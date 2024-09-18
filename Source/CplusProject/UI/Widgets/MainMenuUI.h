#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuUI.generated.h"

UCLASS()
class CPLUSPROJECT_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()
public:
	// ============================= PROPERTIES =============================
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* startGameButton;
	UFUNCTION()
	void StartGame();
protected:
	// ============================= FUNCTIONS =============================
	virtual void NativeConstruct() override;


};
