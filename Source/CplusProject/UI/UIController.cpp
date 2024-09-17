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
	if (gameOverUIClass)
	{
		gameOverPanel = CreateWidget<UGameOverUI>(GetWorld(), gameOverUIClass);
		gameOverPanel->AddToViewport();
		gameOverPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("could not getgameOverUIClass"))
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

	if (lockUIClass)
	{
		lockPanel = CreateWidget<ULockUI>(GetWorld(), lockUIClass);
		lockPanel->AddToViewport();
		lockPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("could not get lockUIClass"))
	}

	if (enourageInteractionUIClass)
	{
		encourageInteractionPanel = CreateWidget<UUserWidget>(GetWorld(), enourageInteractionUIClass);
		encourageInteractionPanel->AddToViewport();
		encourageInteractionPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("could not get enourageInteractionUIClass"))
	}
}

void AUIController::OpenInteractionUI()
{
	interactionPanel->SetVisibility(ESlateVisibility::Visible);
}

void AUIController::UpdateInteractionUI(const FItemData& data)
{
	switch (data.itemType)
	{
		case ItemType::Interactable:
		{
			interactionPanel->UpdateWidget(data.description);
			if (interactionPanel->GetVisibility() == ESlateVisibility::Collapsed)
			{
				interactionPanel->SetVisibility(ESlateVisibility::Visible);
			}
			break;
		}
		case ItemType::Lock:
		{
			OpenLockUI();
			break;
		}
	}
}

void AUIController::CloseAllInteractionUI()
{
	if (interactionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseInteractionUI();
	if (encourageInteractionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseEncourageInteractUI();
	if (lockPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseLockUI();
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
	lockPanel->SetVisibility(ESlateVisibility::Collapsed);
}
void AUIController::OpenEncourageInteractUI()
{
	encourageInteractionPanel->SetVisibility(ESlateVisibility::Visible);
}

void AUIController::CloseEncourageInteractUI()
{
	encourageInteractionPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void AUIController::OpenMainMenu()
{
	mainMenuPanel->SetVisibility(ESlateVisibility::Visible);
}

void AUIController::CloseMainMenu()
{
	mainMenuPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void AUIController::OpenGameOverUI()
{
	gameOverPanel->SetVisibility(ESlateVisibility::Visible);
}

void AUIController::CloseGameOverUI()
{
	gameOverPanel->SetVisibility(ESlateVisibility::Collapsed);
}
