#include "UIController.h"
#include "Kismet/GameplayStatics.h"

void AUIController::SwitchToUIControls()
{
	GetOwningPlayerController()->SetShowMouseCursor(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(inputModeUI);
}
void AUIController::SwitchToPlayerControls()
{
	GetOwningPlayerController()->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(gameInputMode);
}
