// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Components/AchievementComponent.h"
#include "GameLogic/SaveTheGame.h"
#include "Gamelogic/Achievement.h"
#include "GameLogic/AchievementData.h"
#include "Character/AchievementSystemCharacter.h"
#include "Interfaces/IObjectType.h"
#include "World/Shapes/BaseShape.h"

//engine 
#include "Kismet/GameplayStatics.h"



UAchievementComponent::UAchievementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    
    InitializeAchievements(); // Ensure achievements are initialized before loading
    LoadAchievements(); //Loading achievements progress if there's any save
}

void UAchievementComponent::CheckAllAchievementsCompleted()
{
    for (UAchievement* Achievement : Achievements)
    {
        if (Achievement && Achievement->GetAchievementName() != "All Trophies Collected" && !Achievement->IsUnlocked())
        {
            return; // If any achievement is not unlocked, exit the function
        }
    }

    TrackProgress("All Trophies Collected", 1.f);
}

void UAchievementComponent::TrackCharacterMetrics()
{
    OnDistanceTraveled.AddDynamic(this, &UAchievementComponent::HandleDistanceTraveled);
    OnJumpMade.AddDynamic(this, &UAchievementComponent::HandleJumpMade);

}

void UAchievementComponent::BeginPlay()
{
	Super::BeginPlay();

    TrackCharacterMetrics();
    HandleBeginPlayAchievements();
    TrackCombatMetrics();
    TrackOverlapEvents();

}

void UAchievementComponent::TrackCombatMetrics()
{
    OnProjectileHit.AddDynamic(this, &UAchievementComponent::HandleHitObject);
}

void UAchievementComponent::TrackOverlapEvents()
{
    OnLocationTriggered.AddDynamic(this, &UAchievementComponent::HandleLocationTriggered);
}

void UAchievementComponent::HandleDistanceTraveled(float Distance)
{
    //UE_LOG(LogTemp, Warning, TEXT("UAchievementComponent::HandleDistanceTraveled(float Distance)"))
    
    TrackProgress("Love Jogging", Distance);
}

void UAchievementComponent::HandleJumpMade()
{
    TrackProgress("Break your Knees", 1.f);
}

void UAchievementComponent::HandleHitObject(float HitDistance, UObject* HitObject)
{
    if (HitObject && HitObject->GetClass()->ImplementsInterface(UIObjectType::StaticClass()))
    {
        FString ObjectType = IIObjectType::Execute_GetObjectType(HitObject);

        //UE_LOG(LogTemp, Warning, TEXT("HandleHitObject: distance %f, object type %s"), HitDistance, *ObjectType);

        for (UAchievement* Achievement : Achievements)
        {
            if (Achievement->GetAchievementName() == "Baby Range" && ObjectType == "Box" && HitDistance >= 1000.f)
            {
                TrackProgress("Baby Range", 1.f);
            }
            else if (Achievement->GetAchievementName() == "Exceptional" && ObjectType == "Circle" && HitDistance >= 2000.f)
            {
                TrackProgress("Exceptional", 1.f);
            }
            else if (Achievement->GetAchievementName() == "Dead Eye" && ObjectType == "Torus" && HitDistance >= 3000.f)
            {
                TrackProgress("Dead Eye", 1.f);
            }
            else if (Achievement->GetAchievementName() == "Total Hits")
            {
                TrackProgress("Total Hits", 1.f);
            }
        }
    }
}

void UAchievementComponent::HandleLocationTriggered(FString LocationName)
{
    for (UAchievement* Achievement : Achievements)
    { 
        if (Achievement->GetAchievementName() == "The King of the World" && LocationName == "The King of the World")
        {
            TrackProgress("The King of the World", 1.f);
        }
        else if (Achievement->GetAchievementName() == "This is Sparta" && LocationName == "This is Sparta")
        {
            TrackProgress("This is Sparta", 1.f);
        }
    }
}

void UAchievementComponent::HandleBeginPlayAchievements()
{
    TrackProgress("The Game Begins", 1.f);
}

UAchievement* UAchievementComponent::FindAchievementByName(FName AchievementName)
{
    
    if (Achievements.Num() == 0)
    {
        //UE_LOG(LogTemp, Error, TEXT("Achievements array is empty in FindAchievementByName"));
        return nullptr;
    }

    for (UAchievement* Achievement : Achievements)
    {
        if (!Achievement)
        {
            //UE_LOG(LogTemp, Error, TEXT("Found a null pointer in Achievements array in FindAchievementByName"));
            continue;
        }
        if (Achievement->GetAchievementName() == AchievementName)
        {
            return Achievement;
        }
    }

    //UE_LOG(LogTemp, Warning, TEXT("No achievement with name '%s' found in FindAchievementByName"), *AchievementName.ToString());
    return nullptr;
}

void UAchievementComponent::InitializeAchievements()
{   
    // Create and initialize all the achievements
    Achievements.Empty(); // Clear existing achievements

    // Create and initialize all the achievements

    UAchievement* AllTrophiesAchievement = CreateAchievement("All Trophies Collected", "Unlock all other achievements", 1);
    if (AllTrophiesAchievement)
    {
        Achievements.Add(AllTrophiesAchievement);
    }

    UAchievement* GameBeginsAchievement = CreateAchievement("The Game Begins", "Start the game for the first time", 1);
    if (GameBeginsAchievement)
    {
        Achievements.Add(GameBeginsAchievement);
    }

    UAchievement* LoveJoggingAchievement = CreateAchievement("Love Jogging", "Travel 1000 meters", 1000.0f);
    if (LoveJoggingAchievement)
    {
        Achievements.Add(LoveJoggingAchievement);
    }

    UAchievement* BreakYourKneesAchievement = CreateAchievement("Break your Knees", "Jump 50 times", 50);
    if (BreakYourKneesAchievement)
    {
        Achievements.Add(BreakYourKneesAchievement);
    }

    UAchievement* BabyRangeAchievement = CreateAchievement("Baby Range", "Hit 10 boxes from at least 10 meters away", 10);
    if (BabyRangeAchievement)
    {
        Achievements.Add(BabyRangeAchievement);
    }

    UAchievement* ExceptionalAchievement = CreateAchievement("Exceptional", "Hit 10 circles from at least 20 meters away", 10);
    if (ExceptionalAchievement)
    {
        Achievements.Add(ExceptionalAchievement);
    }

    UAchievement* DeadEyeAchievement = CreateAchievement("Dead Eye", "Hit 10 torus from at least 30 meters away", 10);
    if (DeadEyeAchievement)
    {
        Achievements.Add(DeadEyeAchievement);
    }

    UAchievement* TotalHitsAchievement = CreateAchievement("Total Hits", "Hit a total of 100 objects", 100);
    if (TotalHitsAchievement)
    {
        Achievements.Add(TotalHitsAchievement);
    }

    UAchievement* KingOfTheWorldAchievement = CreateAchievement("The King of the World", "Reach the highest point on the map.", 1);
    if (KingOfTheWorldAchievement)
    {
        Achievements.Add(KingOfTheWorldAchievement);
    }

    UAchievement* ThisIsSpartaAchievement = CreateAchievement("This is Sparta", "Jump down on a black box. The highest point on the map is a perfect spot for jumping", 1);
    if (ThisIsSpartaAchievement)
    {
        Achievements.Add(ThisIsSpartaAchievement);
    }

    // Broadcast initial state of achievements
    for (UAchievement* Achievement : Achievements)
    {
        if (Achievement)
        {
            OnAchievementUpdated.Broadcast(Achievement->GetAchievementName().ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failind to broadcast, Achievement is null"));
        }
    }
}

UAchievement* UAchievementComponent::CreateAchievement(const FString& Name, const FString& Description, float Goal)
{
    UAchievement* NewAchievement = NewObject<UAchievement>();
    
    if (NewAchievement)
    {
        NewAchievement->SetAchievementName(FName(*Name));
        NewAchievement->SetDescription(Description); 
        NewAchievement->SetGoal(Goal);
       
        return NewAchievement;
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("Failed to create achievement: %s"), *Name);
        return nullptr;
    }
}

void UAchievementComponent::TrackProgress(FName AchievementName, float Progress)
{
    UAchievement* Achievement = FindAchievementByName(AchievementName);

    if (Achievement)
    {
        if (Achievement->IsUnlocked()) return;

        Achievement->IncrementProgress(Progress);

        //FString AchievementInfo = FString::Printf(TEXT("%s: Progress: %.2f Goal: %.2f"), *AchievementName.ToString(), Achievement->GetProgress(), Achievement->GetGoal());
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *AchievementInfo);

        // Check if the achievement is now unlocked
        if (Achievement->GetProgress() >= Achievement->GetGoal())
        {
            UnlockAchievement(AchievementName);
        }
        
        // Trigger the delegate to notify listeners about the update
        OnAchievementUpdated.Broadcast(AchievementName.ToString());
    }
}

void UAchievementComponent::SaveAchievements()
{
    USaveTheGame* SaveGameInstance = Cast<USaveTheGame>(UGameplayStatics::CreateSaveGameObject(USaveTheGame::StaticClass()));
    if (!SaveGameInstance) return;

    SaveGameInstance->ClearSavedAchievements();
    for (UAchievement* Achievement : Achievements)
    {
        if (Achievement)
        {
            FAchievementData AchievementData;
            
            AchievementData.AchievementName = Achievement->GetAchievementName();
            AchievementData.Description = Achievement->GetDescription();
            AchievementData.bIsUnlocked = Achievement->IsUnlocked();
            AchievementData.Progress = Achievement->GetProgress();
            AchievementData.Goal = Achievement->GetGoal();
            
            SaveGameInstance->AddAchievement(AchievementData);
            
        }
    }

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("AchievementSlot"), 0);
}

void UAchievementComponent::LoadAchievements()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("AchievementSlot"), 0))
    {
        USaveTheGame* LoadGameInstance = Cast<USaveTheGame>(UGameplayStatics::LoadGameFromSlot(TEXT("AchievementSlot"), 0));
        if (LoadGameInstance)
        {
            //UE_LOG(LogTemp, Log, TEXT("Achievements loaded successfully"));

            Achievements.Empty();
            for (const FAchievementData& AchievementData : LoadGameInstance->GetSavedAchievements())
            {
                UAchievement* NewAchievement = CreateDefaultSubobject<UAchievement>(*AchievementData.AchievementName.ToString());
                if (NewAchievement)
                {
                    NewAchievement->SetAchievementName(AchievementData.AchievementName); 
                    NewAchievement->SetDescription(AchievementData.Description); 
                    NewAchievement->SetbIsUnlocked(AchievementData.bIsUnlocked); 
                    NewAchievement->SetProgress(AchievementData.Progress); 
                    NewAchievement->SetGoal(AchievementData.Goal);
                    Achievements.Add(NewAchievement);

                    // Broadcast the updated achievement name for HUD display
                    OnAchievementUpdated.Broadcast(NewAchievement->GetAchievementName().ToString());
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to create achievement object for: %s"), *AchievementData.AchievementName.ToString());
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load achievements"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save game found for achievements"));
    }
}

void UAchievementComponent::EraseAchievements()
{
    //UE_LOG(LogTemp, Warning, TEXT ("in UAchievementComponent::EraseAchievements() EraseAchievements()"))
    
    // Reset all achievements
    for (UAchievement* Achievement : Achievements)
    {
        if (Achievement)
        {
            Achievement->SetProgress(0.f);
            Achievement->SetbIsUnlocked(false);
            OnAchievementUpdated.Broadcast(Achievement->GetAchievementName().ToString());
        }
    }

    UGameplayStatics::DeleteGameInSlot(TEXT("AchievementSlot"), 0);
}

void UAchievementComponent::UnlockAchievement(FName AchievementName)
{
    UAchievement* Achievement = FindAchievementByName(AchievementName);
    
    if (Achievement && !Achievement->IsUnlocked())
    {
        Achievement->SetbIsUnlocked(true);
        
        // Perform any additional actions on unlock
        
        //UE_LOG(LogTemp, Warning, TEXT("Achievement Unlocked: %s"), *AchievementName.ToString());

        // Check if "All Trophies Collected" achievement needs to be unlocked
        if (AchievementName != "All Trophies Collected")
        {
            CheckAllAchievementsCompleted();
        }
    }
}

