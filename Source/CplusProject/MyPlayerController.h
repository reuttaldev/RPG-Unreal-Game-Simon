#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "MyPlayerController.generated.h"

UCLASS(Abstract)
class CPLUSPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* actionMove= nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* actionInteract= nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputMappingContext* inputMappingContext = nullptr;

protected:
	// on enable and on disable. pawn = player. 
	virtual void OnPossess(APawn* pawn) override;
	virtual void OnUnPossess() override;

	void HandleInteractInput();
	void HandleMoveInput(const FInputActionValue& inputActionValue);
private:
	UPROPERTY()
	UEnhancedInputComponent* inputComponentPtr = nullptr;

	UPROPERTY()
	ACharacter* playerPtr = nullptr;
};
