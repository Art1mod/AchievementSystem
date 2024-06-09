// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Triggers/LocationTriggerBase.h"
#include "Components/BoxComponent.h"
#include "Character/AchievementSystemCharacter.h"

// Sets default values
ALocationTriggerBase::ALocationTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VolumeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("VolumeBox"));
	VolumeBox->SetCollisionProfileName("Trigger");
	VolumeBox->OnComponentBeginOverlap.AddDynamic(this, &ALocationTriggerBase::OnOverlapBegin);
	RootComponent = VolumeBox;
}

// Called when the game starts or when spawned
void ALocationTriggerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocationTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ALocationTriggerBase::GetObjectType_Implementation() const
{
	return ObjectType;
}

void ALocationTriggerBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAchievementSystemCharacter* AchievementCharacter = Cast<AAchievementSystemCharacter>(OtherActor);
	if (AchievementCharacter)
	{
		UAchievementComponent* AchievementComponent = AchievementCharacter->GetAchievementComponent();
		
		if (AchievementComponent)
		{
			AchievementComponent->OnLocationTriggered.Broadcast(ObjectType);
		}
	}
}

