#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIController.generated.h"

UCLASS(Abstract)
class CPLUSPROJECT_API AUIController : public AHUD
{
	GENERATED_BODY()
protected:
	// ============================= FUNCTIONS =============================
	FInputModeUIOnly inputModeUI;
	FInputModeGameOnly gameInputMode;
	// ============================= FUNCTIONS =============================
	void SwitchToUIControls();
	void SwitchToPlayerControls();
public:
	virtual void CloseAll() {};// tried to do =0 and make the class abstract, getting UIController even though I cannot understand where I am instantiating it and I implement the function in the inheriting classes

};
