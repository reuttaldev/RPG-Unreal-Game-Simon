#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenu.h"
#include "LockUI.h"
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
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenu> mainMenuClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInteractionUI> interactionUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULockUI> lockUIClass;

	// ============================= FUNCTIONS =============================
	void UpdateInteractionUI(const FItemData& text);
	void CloseUI();
	// when the player gets close enough to an intractable object, i.e. this object is in focus, then a popup will appear to let the player know it can interact with it.
	void OpenEncourageInteractUI();
	void CloseEncourageInteractUI();
protected:
	virtual void BeginPlay() override;

private:
	// ============================= PROPERTIES =============================
	UPROPERTY()
	UInteractionUI* interactionPanel;
	UMainMenu* mainMenuPanel;
	ULockUI* lockPanel;

	// ============================= FUNCTIONS =============================
	void CloseInteractionUI();
	void OpenLockUI();
	void CloseLockUI();
	void OpenInteractionUI();
};
