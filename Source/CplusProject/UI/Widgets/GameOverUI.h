#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuUI.h"
#include "GameOverUI.generated.h"

UCLASS()
class CPLUSPROJECT_API UGameOverUI : public UMainMenuUI
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	UButton* quitGameButton;
private:
	// ============================= FUNCTIONS =============================
	UFUNCTION()
	inline void QuitGame() 
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
	inline virtual void NativeConstruct() override
	{
		Super::NativeConstruct();
		quitGameButton->OnClicked.AddDynamic(this, &UGameOverUI::QuitGame);
	}

};
