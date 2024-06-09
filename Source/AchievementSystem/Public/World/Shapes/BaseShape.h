// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IObjectType.h"
#include "BaseShape.generated.h"

UCLASS()
class ACHIEVEMENTSYSTEM_API ABaseShape : public AActor, public IIObjectType
{
	GENERATED_BODY()

public:

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	ABaseShape();

	virtual void Tick(float DeltaTime) override;

	// Implement GetObjectType from the IObjectTypeInterface
	virtual FString GetObjectType_Implementation() const override;

protected:
	

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	// Properties & Variables
	UPROPERTY(EditDefaultsOnly, Category = "Object Type")
	FString ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitSparkles;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
};
