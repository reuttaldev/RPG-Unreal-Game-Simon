#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenu.h"
#include "LockUI.h"
#include "GameOverUI.h"
#include "InteractionUI.h"
#include "../Structs/ItemData.h"
#include "UIController.generated.h"


UCLASS()
class CPLUSPROJECT_API AUIController : public AHUD
{
	GENERATED_BODY()
	
public:
	// ============================= PROPERTIES =============================
	// need to be chosen in the editor
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UMainMenu> mainMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UGameOverUI> gameOverUIClass;
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UInteractionUI> interactionUIClass;
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UUserWidget> enourageInteractionUIClass;
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<ULockUI> lockUIClass;

	// ============================= FUNCTIONS =============================
	void UpdateInteractionUI(const FItemData& text);
	void CloseAllInteractionUI();
	// when the player gets close enough to an intractable object, i.e. this object is in focus, then a popup will appear to let the player know it can interact with it.
	void OpenEncourageInteractUI();
	void CloseEncourageInteractUI();
	void OpenMainMenu();
	void CloseMainMenu();
	void OpenGameOverUI();
	void CloseGameOverUI();
protected:
	virtual void BeginPlay() override;

private:
	// ============================= PROPERTIES =============================
	UPROPERTY()
	UInteractionUI* interactionPanel;
	UMainMenu* mainMenuPanel;
	UGameOverUI* gameOverPanel;
	ULockUI* lockPanel;
	UUserWidget* encourageInteractionPanel;

	// ============================= FUNCTIONS =============================
	void CloseInteractionUI();
	void OpenInteractionUI();
	void OpenLockUI();
	void CloseLockUI();
};
