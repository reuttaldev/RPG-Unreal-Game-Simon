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

void AUIController::CloseUI()
{
	if (interactionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseInteractionUI();
	else
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
}

void AUIController::CloseEncourageInteractUI()
{
}