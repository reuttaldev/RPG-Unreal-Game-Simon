#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "UI/UIController.h"
#include "Interfaces/InteractionInterface.h"
#include "MyPlayerController.generated.h"

UCLASS(Abstract)
class CPLUSPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// ============================= PROPERTIES =============================

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* actionMove= nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* actionInteract= nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputMappingContext* inputMappingContext = nullptr;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector2D direction;
protected:
	// ============================= FUNCTIONS =============================
	virtual void BeginPlay() override;
	// on enable and on disable. pawn = player. 
	virtual void OnPossess(APawn* pawn) override;
	virtual void OnUnPossess() override;

private:
	// ============================= PROPERTIES =============================

	UPROPERTY()
	UEnhancedInputComponent* inputComponentPtr = nullptr;

	UPROPERTY()
	ACharacter* playerPtr = nullptr;
	UPROPERTY()
	AUIController* uiController= nullptr;
	// the actor that we last collided with which implements the interaction interface
	TScriptInterface<IInteractionInterface> lastHitActor= nullptr;
	// this is set to true when we are in close proximity of an intractable object
	bool canInteract = false;
	// are we currently interacting with something?
	bool isInteracting = false;
// ============================= FUNCTIONS =============================
	//will be called on collision enter. here I will check if I hit anything that inherits from InteractionInterface
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// called when we collided with an item which inherits from InteractionInterface, and the player pressed the interact action (E, Enter, etc
	void HandleInteractInput();
	void HandleMoveInput(const FInputActionValue& inputActionValue);
};
