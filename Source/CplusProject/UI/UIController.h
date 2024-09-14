#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenu.h"
#include "LockUI.h"
#include "InteractionUI.h"
#include "UIController.generated.h"


UCLASS()
class CPLUSPROJECT_API AUIController : public AHUD
{
	GENERATED_BODY()
	
public:
	// need to be chosen in the editor
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenu> mainMenuClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInteractionUI> interactionUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULockUI> lockUIClass;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UInteractionUI* interactionPanel;
	UMainMenu* mainMenuPanel;
	ULockUI* lockPanel;

	void OpenInteractionUI();
	void UpdateInteractionUI(const FString& text);
	void CloseInteractionUI();
	void OpenLockUI();
	void CloseLockUI();
};
