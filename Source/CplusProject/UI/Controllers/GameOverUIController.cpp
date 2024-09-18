#include "GameOverUIController.h"

void AGameOverUIController::BeginPlay()
{
	Super::BeginPlay();
	UGameOverUI* gameOverPanel = CreateWidget<UGameOverUI>(GetWorld(), gameOverUIClass);
	gameOverPanel->AddToViewport();
	inputModeUI.SetWidgetToFocus(gameOverPanel->TakeWidget());
	SwitchToUIControls();
}
