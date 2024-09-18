#include "MainMenuUI.h"

void UMainMenuUI::StartGame()
{

	UE_LOG(LogTemp, Warning, TEXT("start game button was pressed"));
	UGameplayStatics::OpenLevel(GetWorld(), "Room1");
}

void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
    startGameButton->OnClicked.AddDynamic(this, &UMainMenuUI::StartGame);
}


