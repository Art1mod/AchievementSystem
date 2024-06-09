#pragma once

#include "CoreMinimal.h"
#include "AchievementData.generated.h"

//Used specifically for saving and loading the state of achievements
USTRUCT(BlueprintType)
struct FAchievementData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AchievementName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked {false};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Progress { 0.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Goal { 0.f };
};
