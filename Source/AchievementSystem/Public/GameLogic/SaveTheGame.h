// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AchievementData.h"
#include "SaveTheGame.generated.h"



/**
 * 
 */


UCLASS()
class ACHIEVEMENTSYSTEM_API USaveTheGame : public USaveGame
{
	GENERATED_BODY()

public:

    //==================================================================================
    // FUNCTIONS
    //==================================================================================

    UFUNCTION()
    void ClearSavedAchievements();
    
    UFUNCTION()
    void AddAchievement(const FAchievementData& AchievementData);

private:
    
    //==================================================================================
    // PROPERTIES & VARIABLES
    //==================================================================================

    UPROPERTY()
    TArray<FAchievementData> SavedAchievements;

public:

    //==================================================================================
    // Getters & Setters
    //==================================================================================

    FORCEINLINE TArray<FAchievementData> GetSavedAchievements() const { return SavedAchievements; }

};
