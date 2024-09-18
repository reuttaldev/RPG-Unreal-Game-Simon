#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "UI/Controllers/GameUIContoller.h"
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
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector2D direction;
	// ============================= FUNCTIONS =============================
	AMyPlayerController();
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
	UCapsuleComponent* playerCollisionComponent = nullptr;
	UPROPERTY()
	AGameUIContoller* uiController= nullptr;
	UPROPERTY()
	// creating a copy of the item data belonging to the actor we last interacted with. We cannot keep the actor since the reference will become invalid at the end of the OnOverlap functions, and there is no point of creating a copy of the whole thing
	FItemData lastInteractedItemData;
	// this is set to true when we are in close proximity of an intractable object
	bool canInteract;
	// are we currently interacting with something?
	bool isInteracting;
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
