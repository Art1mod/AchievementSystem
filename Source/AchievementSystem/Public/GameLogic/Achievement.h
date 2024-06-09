// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Achievement.generated.h"


/**
 * 
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API UAchievement : public UObject
{
	GENERATED_BODY()

public:


    //==================================================================================
    // FUNCTIONS
    //==================================================================================

    UFUNCTION()
    void IncrementProgress(float Amount);



private:

    //==================================================================================
    // PROPERTIES & VARIABLES
    //==================================================================================

    UPROPERTY()
    FName AchievementName;

    UPROPERTY()
    FString Description;

    UPROPERTY()
    bool bIsUnlocked;

    UPROPERTY()
    float Progress;

    UPROPERTY()
    float Goal;

    //==================================================================================
    // FUNCTIONS
    //==================================================================================
    
    UFUNCTION()
    void CheckProgress();

   
public:

    //==================================================================================
    // Getters & Setters 
    //==================================================================================
    
    FORCEINLINE FName GetAchievementName() const { return AchievementName; }
    FORCEINLINE FString GetDescription() const { return Description; }
    FORCEINLINE bool IsUnlocked() const { return bIsUnlocked; }
    FORCEINLINE float GetProgress() const { return Progress; }
    FORCEINLINE float GetGoal() const { return Goal; }

    FORCEINLINE void SetAchievementName(FName AchievementNameIn) { AchievementName = AchievementNameIn; }
    FORCEINLINE void SetDescription(FString DescriptionIn) { Description = DescriptionIn; }
    FORCEINLINE void SetbIsUnlocked(bool bIsUnlockedIn) { bIsUnlocked = bIsUnlockedIn; }
    FORCEINLINE void SetProgress(float ProgressIn) { Progress = ProgressIn; }
    FORCEINLINE void SetGoal(float GoalIn) { Goal = GoalIn; }
};
