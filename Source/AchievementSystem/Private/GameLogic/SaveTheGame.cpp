// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/SaveTheGame.h"

void USaveTheGame::ClearSavedAchievements()
{
	SavedAchievements.Empty();
}

void USaveTheGame::AddAchievement(const FAchievementData& AchievementData)
{
	SavedAchievements.Add(AchievementData);
}
