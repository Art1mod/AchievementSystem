// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ConfirmationDialog.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UConfirmationDialog::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UConfirmationDialog::HandleConfirmClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UConfirmationDialog::HandleCancelClicked);
	}
}

void UConfirmationDialog::SetMessage(FText Message)
{
	if (MessageText)
	{
		MessageText->SetText(Message);
	}
}

void UConfirmationDialog::HandleConfirmClicked()
{
	OnConfirm.Broadcast();
	RemoveFromParent();
}

void UConfirmationDialog::HandleCancelClicked()
{
	RemoveFromParent();
}
