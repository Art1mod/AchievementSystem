// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AchievementSlot.generated.h"

class UTextBlock;
class UAchievement;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API UAchievementSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	void UpdateAchievementInfo();

protected:

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	virtual void NativeConstruct() override;

private:

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(VisibleAnywhere, Category = "Achievement Slot")
	UAchievement* AchievementReference;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Achievement Slot")
	UTextBlock* AchievementName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Achievement Slot")
	UTextBlock* AchievementDescription;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Achievement Slot")
	UTextBlock* AchievementProgress;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Achievement Slot")
	UTextBlock* AchievementGoal;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Achievement Slot")
	UProgressBar* AchievementProgressBar;

public:

	//==================================================================================
	// Getters & Setters
	//==================================================================================
	
	FORCEINLINE UAchievement* GetAchievementReference() const { return AchievementReference; }

	FORCEINLINE void SetAchievementReference(UAchievement* AchievementIn) { AchievementReference = AchievementIn; };
};
