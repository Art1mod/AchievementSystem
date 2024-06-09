// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "UserInterface/AchievementBox.h"
#include "Character/AchievementSystemCharacter.h"
#include "Components/AchievementComponent.h"
#include "UserInterface/AchievementSlot.h"
#include "GameLogic/Achievement.h"

//engine
#include "Components/WrapBox.h"

void UAchievementBox::InitializeAchievementBox()
{
	if (!AchievementComponentReference || !AchievementSlotClass || !AchievementBoxWrapBox)
	{
		UE_LOG(LogTemp, Error, TEXT("AchievementBox initialization failed: Invalid references"));
		return;
	}

	AchievementBoxWrapBox->ClearChildren();
	AchievementSlotMap.Empty();

	// Iterate through all achievements retrieved from the achievement component

	for (UAchievement* const& Achievement : AchievementComponentReference->GetAllAchievements())
	{
		UAchievementSlot* AchievementSlot = CreateWidget<UAchievementSlot>(this, AchievementSlotClass);
		if (!AchievementSlot)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create AchievementSlot widget"));
			continue;
		}

		/*
		AchievementSlot->SetAchievementReference(Achievement);
		AchievementBoxWrapBox->AddChildToWrapBox(AchievementSlot);
		AchievementSlotMap.Add(Achievement->GetAchievementName().ToString(), AchievementSlot);
		*/
		//
		if (AchievementSlot && AchievementBoxWrapBox)
		{
			AchievementSlot->SetAchievementReference(Achievement);
			AchievementBoxWrapBox->AddChildToWrapBox(AchievementSlot);
			AchievementSlotMap.Add(Achievement->GetAchievementName().ToString(), AchievementSlot);
		}
		
	}
}

void UAchievementBox::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<AAchievementSystemCharacter>(GetOwningPlayerPawn());
	if (!PlayerCharacter)
	{
		//UE_LOG(LogTemp, Error, TEXT("AchievementBox initialization failed: PlayerCharacter is nullptr"));
		return;
	}

	AchievementComponentReference = PlayerCharacter->GetAchievementComponent();
	if (!AchievementComponentReference)
	{
		//UE_LOG(LogTemp, Error, TEXT("AchievementBox initialization failed: AchievementComponentReference is nullptr"));
		return;
	}

	// Binding the UpdateAchievement function to the OnAchievementUpdated event to update the achievement information displayed in the UI
	AchievementComponentReference->OnAchievementUpdated.AddDynamic(this, &UAchievementBox::UpdateAchievement);
	InitializeAchievementBox();
}

void UAchievementBox::UpdateAchievement(const FString& AchievementName)
{
	UAchievementSlot** AchievementSlotPtr = AchievementSlotMap.Find(AchievementName);
	if (!AchievementSlotPtr)
	{
		//UE_LOG(LogTemp, Error, TEXT("AchievementSlot not found for Achievement: %s"), *AchievementName);
		return;
	}

	UAchievementSlot* AchievementSlot = *AchievementSlotPtr;
	if (!AchievementSlot)
	{
		//UE_LOG(LogTemp, Error, TEXT("AchievementSlot is nullptr"));
		return;
	}

	// Update the achievement information displayed in the UI
	AchievementSlot->UpdateAchievementInfo();
}