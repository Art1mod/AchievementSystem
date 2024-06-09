// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AchievementComponent.generated.h"

//==================================================================================
// Delegates 
//==================================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAchievementUpdatedDelegate, const FString&, AchievementName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDistanceTraveledDelegate, float, DistanceTraveled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpMadeDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitObjectDelegate, float, HitDistance, UObject*, HitObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocationTriggeredDelegate, FString, LocationName);


class UAchievement;
class USoundCue;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACHIEVEMENTSYSTEM_API UAchievementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(VisibleAnywhere, Category = "Achievements")
	FAchievementUpdatedDelegate OnAchievementUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Achievements")
	FOnDistanceTraveledDelegate OnDistanceTraveled;
	
	UPROPERTY(BlueprintAssignable, Category = "Achievements")
	FOnJumpMadeDelegate OnJumpMade;

	UPROPERTY(BlueprintAssignable, Category = "Achievements")
	FOnHitObjectDelegate OnProjectileHit;

	UPROPERTY(BlueprintAssignable, Category = "Achievements")
	FOnLocationTriggeredDelegate OnLocationTriggered;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	UAchievementComponent();
	
	//moved here from private
	//Used in Menu
	UFUNCTION()
	void SaveAchievements();

	//moved here from private
	//Used in Menu 
	UFUNCTION()
	void EraseAchievements();


protected:
	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================	

	//All available achievements 
	TArray<UAchievement*> Achievements;
	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================


	// Check if all achievements except the "All Trophies Collected" are completed
	UFUNCTION()
	void CheckAllAchievementsCompleted();

	//Bindings of CharacterMetrics
	UFUNCTION()
	void TrackCharacterMetrics();

	//Bindings of CombatMetrics
	UFUNCTION()
	void TrackCombatMetrics();

	//Bindings of OverlapEvents
	UFUNCTION()
	void TrackOverlapEvents();

	//Handles DistanceTraveled achievements
	UFUNCTION()
	void HandleDistanceTraveled(float Distance);

	//Handles jump achievements
	UFUNCTION()
	void HandleJumpMade();

	//Handles combat achievements
	UFUNCTION()
	void HandleHitObject(float HitDistance, UObject* HitObject);
	
	//Handles LocationTriggered achievements
	UFUNCTION()
	void HandleLocationTriggered(FString LocationName);

	//Handles start the game achievements
	UFUNCTION()
	void HandleBeginPlayAchievements();

	//Track the progress of the provided achievement
	UFUNCTION()
	void TrackProgress(FName AchievementName, float Progress);

	UFUNCTION()
	void LoadAchievements();

	UFUNCTION()
	void UnlockAchievement(FName AchievementName);

	UFUNCTION()
	UAchievement* FindAchievementByName(FName AchievementName);

	UFUNCTION()
	void InitializeAchievements();

	UFUNCTION()
	UAchievement* CreateAchievement(const FString& Name, const FString& Description, float Goal);

public:	
	
	//==================================================================================
	// Getters & Setters 
	//==================================================================================

	FORCEINLINE TArray<UAchievement*> GetAllAchievements() const { return Achievements; }
		
};
