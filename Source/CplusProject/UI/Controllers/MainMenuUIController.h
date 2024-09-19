#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIController.h"
#include "CplusProject/UI/Widgets/GameOverUI.h"
#include "MainMenuUIController.generated.h"

UCLASS()
class CPLUSPROJECT_API AMainMenuUIController : public AUIController
{
	GENERATED_BODY()
public:
	// ============================= PROPERTIES =============================
	/// needs to be chosen in the editor
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UMainMenuUI> mainMenuClass;
protected:
	virtual void BeginPlay() override;	
};
