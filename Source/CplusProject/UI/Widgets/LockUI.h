#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LockUI.generated.h"

UCLASS()
class CPLUSPROJECT_API ULockUI : public UUserWidget
{
	GENERATED_BODY()
public:
	// ============================= PROPERTIES =============================
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* redButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* greenButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* blueButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* yellowButton;
};
