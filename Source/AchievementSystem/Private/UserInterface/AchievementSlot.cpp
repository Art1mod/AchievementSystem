// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AchievementSlot.h"
#include "GameLogic/Achievement.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UAchievementSlot::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateAchievementInfo();
}

void UAchievementSlot::UpdateAchievementInfo()
{
	if (AchievementReference)
	{
		AchievementName->SetText(FText::FromName(AchievementReference->GetAchievementName()));
		AchievementDescription->SetText(FText::FromString(AchievementReference->GetDescription()));
		AchievementProgress->SetText(FText::AsNumber(AchievementReference->GetProgress()));
		AchievementGoal->SetText(FText::AsNumber(AchievementReference->GetGoal()));
		AchievementProgressBar->SetPercent(FMath::Clamp(AchievementReference->GetProgress() / AchievementReference->GetGoal(), 0.f, 1.f));
	}
}
