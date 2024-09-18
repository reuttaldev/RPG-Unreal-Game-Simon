#include "MainMenuUIController.h"

void AMainMenuUIController::BeginPlay()
{
	Super::BeginPlay();
	UMainMenuUI* mainMenuPanel = CreateWidget<UMainMenuUI>(GetWorld(), mainMenuClass);
	mainMenuPanel->AddToViewport();
	inputModeUI.SetWidgetToFocus(mainMenuPanel->TakeWidget());
	SwitchToUIControls();
}
