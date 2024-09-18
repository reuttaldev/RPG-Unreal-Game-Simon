#include "GameUIContoller.h"
#include "CplusProject/Interfaces/InteractionInterface.h"
#include "CplusProject/Environment/DoorOpenComponent.h"

void AGameUIContoller::BeginPlay()
{
	Super::BeginPlay();
	interactionPanel = CreateWidget<UInteractionUI>(GetWorld(), interactionUIClass);
	interactionPanel->AddToViewport();
	interactionPanel->SetVisibility(ESlateVisibility::Collapsed);

	lockPanel = CreateWidget<ULockUI>(GetWorld(), lockUIClass);
	lockPanel->AddToViewport();
	lockPanel->SetVisibility(ESlateVisibility::Collapsed);

	encourageInteractionPanel = CreateWidget<UUserWidget>(GetWorld(), enourageInteractionUIClass);
	encourageInteractionPanel->AddToViewport();
	encourageInteractionPanel->SetVisibility(ESlateVisibility::Collapsed);

	SwitchToPlayerControls();
}

void AGameUIContoller::UpdateInteractionUI(const AActor* interactedActor)
{
	if (!interactedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to update interaction UI but actor is null. It has been destroyed elsewhere."));
		return;
	}
	const IInteractionInterface* interfacePtr = Cast<IInteractionInterface>(interactedActor);
	const FItemData& data = interfacePtr->GetItemData();
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
		// the order here matters. In case two components are found
		case ItemType::OpenDoor:
		{
			// change to the scene that we specified in the last opened lock controller 
			interactedActor->FindComponentByClass<UDoorOpenComponent>()->OpenDoor();
			break;
		}
		case ItemType::Lock:
		{
			SetLockController(interactedActor->FindComponentByClass<ULockControllerComponent>());
			OpenLockUI();
			break;
		}
	}
}

void AGameUIContoller::OpenInteractionUI()
{
	interactionPanel->SetVisibility(ESlateVisibility::Visible);
}

void AGameUIContoller::CloseInteractionUI()
{
	interactionPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void AGameUIContoller::OpenLockUI()
{
	inputModeUI.SetWidgetToFocus(lockPanel->TakeWidget());
	SwitchToUIControls();
	lockPanel->SetVisibility(ESlateVisibility::Visible);
	lockPanel->PlaySequence();
}

void AGameUIContoller::CloseLockUI()
{
	SwitchToPlayerControls();
	lockPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void AGameUIContoller::OpenEncourageInteractUI()
{
	encourageInteractionPanel->SetVisibility(ESlateVisibility::Visible);
}

void AGameUIContoller::CloseEncourageInteractUI()
{
	encourageInteractionPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void AGameUIContoller::SetLockController(ULockControllerComponent* newController)
{
	if (!newController)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to update lock component but got nullptr."));
		return;
	}
	lockPanel->SetLockController(newController);
}

void AGameUIContoller::CloseAll()
{
	if (interactionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseInteractionUI();
	if (encourageInteractionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseEncourageInteractUI();
	if (lockPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseLockUI();
}