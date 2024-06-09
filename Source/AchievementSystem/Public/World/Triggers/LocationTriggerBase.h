// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IObjectType.h"
#include "LocationTriggerBase.generated.h"

class UBoxComponent;


UCLASS()
class ACHIEVEMENTSYSTEM_API ALocationTriggerBase : public AActor, public IIObjectType
{
	GENERATED_BODY()
	

public:

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	ALocationTriggerBase();

	virtual void Tick(float DeltaTime) override;

	// Implement the GetObjectType method
	virtual FString GetObjectType_Implementation() const override;

protected:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* VolumeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	FString ObjectType;


	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
