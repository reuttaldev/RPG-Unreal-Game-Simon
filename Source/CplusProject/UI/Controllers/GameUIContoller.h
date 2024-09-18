#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CplusProject/UI/Widgets/LockUI.h"
#include "CplusProject/Structs/ItemData.h"
#include "CplusProject/UI/Widgets/InteractionUI.h"
#include "UIController.h"
#include "GameUIContoller.generated.h"

UCLASS()
class CPLUSPROJECT_API AGameUIContoller : public AUIController
{
	GENERATED_BODY()
public:
	// ============================= PROPERTIES =============================
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UInteractionUI> interactionUIClass;
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UUserWidget> enourageInteractionUIClass;
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<ULockUI> lockUIClass;

	// ============================= FUNCTIONS =============================
	void UpdateInteractionUI(const FItemData& text);
	virtual void CloseAll() override;
	// when the player gets close enough to an intractable object, i.e. this object is in focus, then a popup will appear to let the player know it can interact with it.
	void OpenEncourageInteractUI();
	void CloseEncourageInteractUI();
protected:
	virtual void BeginPlay() override;
private:

	// ============================= PROPERTIES =============================
	UPROPERTY()
	UInteractionUI* interactionPanel;
	UPROPERTY()
	ULockUI* lockPanel;
	UPROPERTY()
	UUserWidget* encourageInteractionPanel;
	// ============================= FUNCTIONS =============================
	void CloseInteractionUI();
	void OpenInteractionUI();
	void OpenLockUI();
	void CloseLockUI();
};
