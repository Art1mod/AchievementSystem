// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AchievementSystemHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/AchievementBox.h"

void AAchievementSystemHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		
		if (MainMenuWidget) 
		{
			MainMenuWidget->AddToViewport(1);
			MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
			bIsMenuVisible = false;
		}
	}

	if (AchievementBoxClass)
	{
		AchievementBoxWidget = CreateWidget<UAchievementBox>(GetWorld(), AchievementBoxClass);

		if (AchievementBoxWidget)
		{
			AchievementBoxWidget->AddToViewport(-1);
			AchievementBoxWidget->SetVisibility(ESlateVisibility::Collapsed);
			bIsAchievementBoxVisible = false;
		}
		
	}
}

void AAchievementSystemHUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController)
		{
			// Show the cursor
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AAchievementSystemHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController)
		{
			// Hide the cursor 
			PlayerController->bShowMouseCursor = false;
		}
	}
}

void AAchievementSystemHUD::ToggleMenu()
{
	if (bIsMenuVisible) 
	{
		HideMenu();
	}
	else 
	{
		DisplayMenu();
	}
}

void AAchievementSystemHUD::ShowAchievementBox()
{
	if (AchievementBoxWidget)
	{
		bIsAchievementBoxVisible = true;
		AchievementBoxWidget->SetVisibility(ESlateVisibility::Visible);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController)
		{
			// Show the cursor 
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AAchievementSystemHUD::HideAchievementBox()
{
	if (AchievementBoxWidget)
	{
		bIsAchievementBoxVisible = false;
		AchievementBoxWidget->SetVisibility(ESlateVisibility::Collapsed);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController)
		{
			// Hide the cursor 
			PlayerController->bShowMouseCursor = false;
		}
	}
}

void AAchievementSystemHUD::ToggleAchievementBox()
{
	if (bIsAchievementBoxVisible)
	{
		HideAchievementBox();
	}
	else 
	{
		ShowAchievementBox();
	}
}


