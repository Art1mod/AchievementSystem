// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "UserInterface/MainMenu.h"
#include "Character/AchievementSystemCharacter.h"
#include "Components/AchievementComponent.h"
#include "UserInterface/ConfirmationDialog.h"

//engine
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind SaveButton click event to SaveProgress function
    if (SaveButton)
    {
        SaveButton->OnClicked.AddDynamic(this, &UMainMenu::SaveProgress);
    }

    // Bind EraseButton click event to EraseProgress function
    if (EraseButton)
    {
        EraseButton->OnClicked.AddDynamic(this, &UMainMenu::EraseProgress);
    }

    // Bind QuitButton click event to QuitGame function
    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
    }
}

void UMainMenu::ShowWarningMessage(FText Message, EWarningMessageType MessageType)
{   
    // Check and remove any existing dialog
    if (CurrentDialog)
    {
        CurrentDialog->RemoveFromParent();
        CurrentDialog = nullptr;
    }

    if (ConfirmationDialogClass)
    {
        CurrentDialog = CreateWidget<UConfirmationDialog>(GetWorld(), ConfirmationDialogClass);
        if (CurrentDialog)
        {
            switch (MessageType)
            {
            case EWarningMessageType::EraseProgress:
                CurrentDialog->OnConfirm.AddDynamic(this, &UMainMenu::EraseConfirmed);
                break;
            case EWarningMessageType::QuitGame:
                CurrentDialog->OnConfirm.AddDynamic(this, &UMainMenu::QuitConfirmed);
                break;
                // Handle other message types as needed
            }

            CurrentDialog->SetMessage(Message);
            CurrentDialog->AddToViewport(2);
        }
    }
}

void UMainMenu::SaveProgress()
{
    //Saving achievements
    AAchievementSystemCharacter* PlayerCharacter = Cast<AAchievementSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        UAchievementComponent* AchievementComponent = PlayerCharacter->FindComponentByClass<UAchievementComponent>();
        if (AchievementComponent)
        {
            AchievementComponent->SaveAchievements();
            
            //UE_LOG(LogTemp, Warning, TEXT("Progress saved successfully!"));
        }
    }
}

void UMainMenu::EraseProgress()
{
    //Show a warning message when the Erase button is clicked
    ShowWarningMessage(FText::FromString("Are you sure you want to erase the game's progress? All deleted progress cannot be recovered."),
        EWarningMessageType::EraseProgress);
}

void UMainMenu::QuitGame()
{
    //Show a warning message when the Quit button is clicked
    ShowWarningMessage(FText::FromString("Are you sure you want to leave the game? All unsaved progress will be lost."),
        EWarningMessageType::QuitGame);
}


void UMainMenu::EraseConfirmed()
{
    //Remove the current dialog and set it to nullptr
    if (CurrentDialog)
    {
        CurrentDialog->RemoveFromParent();
        CurrentDialog = nullptr;
    }

    //Get the player character and its AchievementComponent, then erase achievements
    AAchievementSystemCharacter* PlayerCharacter = Cast<AAchievementSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        UAchievementComponent* AchievementComponent = PlayerCharacter->FindComponentByClass<UAchievementComponent>();
        if (AchievementComponent)
        {
            AchievementComponent->EraseAchievements();
            
            //UE_LOG(LogTemp, Warning, TEXT("Progress erased successfully!"));
        }
    }
}

void UMainMenu::QuitConfirmed()
{
    //Remove the current dialog and set it to nullptr
    if (CurrentDialog)
    {
        CurrentDialog->RemoveFromParent();
        CurrentDialog = nullptr;
    }

    //Quit the game by issuing a console command
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->ConsoleCommand("quit");
    }
}
