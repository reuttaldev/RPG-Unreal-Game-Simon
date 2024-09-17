#include "GameUIContoller.h"

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

void AGameUIContoller::UpdateInteractionUI(const FItemData& data)
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

void AGameUIContoller::CloseAll()
{
	if (interactionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseInteractionUI();
	if (encourageInteractionPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseEncourageInteractUI();
	if (lockPanel->GetVisibility() == ESlateVisibility::Visible)
		CloseLockUI();
}