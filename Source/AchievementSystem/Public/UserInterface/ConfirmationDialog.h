// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationDialog.generated.h"


//==================================================================================
// Delegates 
//==================================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmDelegate);

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class ACHIEVEMENTSYSTEM_API UConfirmationDialog : public UUserWidget
{
	GENERATED_BODY()

public:

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(VisibleAnywhere, Category = "Dialog")
	FOnConfirmDelegate OnConfirm;


	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	//moved from private
	UFUNCTION()
	void SetMessage(FText Message);


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
	UTextBlock* MessageText;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	UFUNCTION()
	void HandleConfirmClicked();

	UFUNCTION()
	void HandleCancelClicked();

};
