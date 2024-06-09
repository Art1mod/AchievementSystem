// Copyright Epic Games, Inc. All Rights Reserved.

//game
#include "Weapons/AchievementSystemProjectile.h"
#include "Interfaces/IObjectType.h"
#include "Components/AchievementComponent.h"
#include "Character/AchievementSystemCharacter.h"

//engine
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AAchievementSystemProjectile::AAchievementSystemProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AAchievementSystemProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AAchievementSystemProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	if (!OtherActor || !OtherComp)
	{
		return;
	}
	
	// Get the player character
	AAchievementSystemCharacter* PlayerCharacter = Cast<AAchievementSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!PlayerCharacter)
	{
		return;
	}

	// Calculate hit distance from player character's location to the hit point
	float HitDistance = FVector::Dist(PlayerCharacter->GetActorLocation(), Hit.ImpactPoint);

	// Broadcast the hit event if the other actor implements IObjectType
	if (OtherActor->Implements<UIObjectType>())
	{
		IIObjectType* ObjectTypeInterface = Cast<IIObjectType>(OtherActor);
		if (ObjectTypeInterface)
		{
			FString ObjectType = ObjectTypeInterface->Execute_GetObjectType(OtherActor);

			// Trigger the projectile hit event in AchievementComponent
			AAchievementSystemCharacter* Character = Cast<AAchievementSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (Character)
			{
				UAchievementComponent* AchievementComponent = Character->GetAchievementComponent();
				if (AchievementComponent)
				{
					//UE_LOG(LogTemp, Warning, TEXT(" Distance before AchievementComponent->OnProjectileHit.Broadcast(HitDistance, OtherActor):  %f"), HitDistance)
					AchievementComponent->OnProjectileHit.Broadcast(HitDistance, OtherActor);
				}
			}
		}
	}

	// Add impulse and destroy projectile if we hit a physics object
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	Destroy();
}