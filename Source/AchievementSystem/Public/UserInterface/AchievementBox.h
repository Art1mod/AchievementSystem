// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AchievementBox.generated.h"


class UWrapBox;
class AAchievementSystemCharacter;
class UAchievementComponent;
class UAchievementSlot;

/**
 * 
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API UAchievementBox : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	virtual void NativeOnInitialized() override;

private:

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================


	UPROPERTY(meta = (BindWidget))
	UWrapBox* AchievementBoxWrapBox;

	UPROPERTY()
	AAchievementSystemCharacter* PlayerCharacter;

	UPROPERTY()
	UAchievementComponent* AchievementComponentReference;

	UPROPERTY(EditDefaultsOnly, Category = "Achievements")
	TSubclassOf<UAchievementSlot> AchievementSlotClass;

	UPROPERTY()
	TMap<FString, UAchievementSlot*> AchievementSlotMap;


	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	UFUNCTION(BlueprintCallable)
	void InitializeAchievementBox();

	UFUNCTION()
	void UpdateAchievement(const FString& AchievementName);

};
