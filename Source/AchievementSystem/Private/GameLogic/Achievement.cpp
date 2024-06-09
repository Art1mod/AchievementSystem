// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Achievement.h"

void UAchievement::IncrementProgress(float Amount)
{
    if (!bIsUnlocked)
    {
        Progress = FMath::Clamp(Progress + Amount, 0.0f, Goal);
    }
}

void UAchievement::CheckProgress()
{
    if (Progress >= Goal)
    {
        bIsUnlocked = true;
    }
}