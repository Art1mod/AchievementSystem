// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

UENUM(BlueprintType)
enum class EWarningMessageType : uint8
{
	EraseProgress,
	QuitGame
};

/**
 * 
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	virtual void NativeConstruct() override;

private:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* EraseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UConfirmationDialog> ConfirmationDialogClass;

	UPROPERTY() 
	UConfirmationDialog* CurrentDialog;
	

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	UFUNCTION() 
	void ShowWarningMessage(FText Message, EWarningMessageType MessageType);
	
	UFUNCTION()
	void SaveProgress();

	UFUNCTION()
	void EraseProgress();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void EraseConfirmed();

	UFUNCTION()
	void QuitConfirmed();
	
};
