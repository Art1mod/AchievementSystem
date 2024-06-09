// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/Shapes/BaseShape.h"
#include "TorusShape.generated.h"

/**
 *
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API ATorusShape : public ABaseShape
{
	GENERATED_BODY()

public:

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	ATorusShape();

	virtual void Tick(float DeltaTime) override;

protected:


	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	// Variables for controlling the movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 50.f; // Movement speed in units per second

	UPROPERTY()
	bool bMovingRight = true; // Flag to indicate movement direction

	// Distance to maintain between leftmost and rightmost positions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Distance = 100.0f;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	float MaxDistance = 500.f; // Adjust this value as needed
};
