// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Shapes/TorusShape.h"
#include "Components/SphereComponent.h" 

ATorusShape::ATorusShape()
{
    ObjectType = "Torus";
}

void ATorusShape::Tick(float DeltaTime)
{
    // Calculate movement distance for this frame
    float MovementDistance = MoveSpeed * DeltaTime;

    // Calculate new location based on movement direction
    FVector NewLocation = GetActorLocation();
    if (bMovingRight)
    {
        NewLocation.Y += MovementDistance;
    }
    else
    {
        NewLocation.Y -= MovementDistance;
    }

    // Update the location
    SetActorLocation(NewLocation, true);

    // Check if the torus has reached the maximum distance
    if (FMath::Abs(NewLocation.Y - StartLocation.Y) >= MaxDistance)
    {
        // Reverse the movement direction
        bMovingRight = !bMovingRight;

        // Reset the starting location
        StartLocation = GetActorLocation();
    }
}