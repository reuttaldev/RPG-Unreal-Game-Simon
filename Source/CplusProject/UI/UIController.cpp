// Fill out your copyright notice in the Description page of Project Settings.


#include "UIController.h"

void AUIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (mainMenuClass)
	{
		mainMenuPanel = CreateWidget<UMainMenu>(GetWorld(), mainMenuClass);
		mainMenuPanel->AddToViewport();
		mainMenuPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("could not get main menu class"))
	}

	if (interactionUIClass)
	{
		interactionPanel = CreateWidget<UInteractionUI>(GetWorld(), interactionUIClass);
		interactionPanel->AddToViewport();
		interactionPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("could not get interactionUIClass"))
	}

	if (lockPanel)
	{
		lockPanel = CreateWidget<ULockUI>(GetWorld(), lockUIClass);
		lockPanel->AddToViewport();
		lockPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("could not get lockUIClass"))
	}
}

void AUIController::OpenInteractionUI()
{
	interactionPanel->SetVisibility(ESlateVisibility::Visible);
}

void AUIController::UpdateInteractionUI(const FString& text)
{
	if (interactionPanel)
	{
		if (interactionPanel->GetVisibility() == ESlateVisibility::Collapsed)
		{
			interactionPanel->SetVisibility()= ESlateVisibility::Visible
		}
		interactionPanel->UpdateWidget(text);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Does not have a reference to interaction panel"));
	}
}

void AUIController::CloseInteractionUI()
{
	interactionPanel->SetVisibility(ESlateVisibility::Collapsed);

}

void AUIController::OpenLockUI()
{
	lockPanel->SetVisibility(ESlateVisibility::Visible);

}

void AUIController::CloseLockUI()
{
	lockPanel	->SetVisibility(ESlateVisibility::Collapsed);

}
