/// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Shapes/BaseShape.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseShape::ABaseShape()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetCollisionProfileName("BlockAllDynamic");

	// Bind the OnHit function to the collision event
	MeshComponent->OnComponentHit.AddDynamic(this, &ABaseShape::OnHit);
}

// Called when the game starts or when spawned
void ABaseShape::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseShape::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitSparkles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitSparkles, Hit.ImpactPoint);
	}
}

// Called every frame
void ABaseShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString ABaseShape::GetObjectType_Implementation() const
{
	return ObjectType;
}