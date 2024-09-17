#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameOverUI.h"
#include "UIController.h"
#include "GameOverUIController.generated.h"

UCLASS()
class CPLUSPROJECT_API AGameOverUIController : public AUIController
{
	GENERATED_BODY()
public:
	// ============================= PROPERTIES =============================
	UPROPERTY(EditDefaultsOnly, Category = "Panels")
	TSubclassOf<UGameOverUI> gameOverUIClass;
	// ============================= FUNCTIONS =============================
protected:
	virtual void BeginPlay() override;

};
