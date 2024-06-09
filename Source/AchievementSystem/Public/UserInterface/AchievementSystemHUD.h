// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AchievementSystemHUD.generated.h"


class UMainMenu;
class UAchievementBox;
/**
 * 
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API AAchievementSystemHUD : public AHUD
{
	GENERATED_BODY()

public:

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowAchievementBox();
	void HideAchievementBox();
	void ToggleAchievementBox();



protected:
	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	void BeginPlay() override;
	

private:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	//It's a control variable for the HUD
	bool bIsMenuVisible;

	//It's a control variable for the HUD
	bool bIsAchievementBoxVisible;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UAchievementBox> AchievementBoxClass;
	
	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UAchievementBox* AchievementBoxWidget;
	
public:

	//==================================================================================
	// Getters and Setters
	//==================================================================================

	FORCEINLINE bool IsAchievementBoxVisible() const { return bIsAchievementBoxVisible; }
	FORCEINLINE bool IsMenuVisible() const { return bIsMenuVisible; }

};
