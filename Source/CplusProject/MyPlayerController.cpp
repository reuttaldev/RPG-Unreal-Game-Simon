#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

// on enable and on disable. pawn = player. This gets called once the controller gets connected to the player that was spawned.
void AMyPlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	inputComponentPtr = Cast<UEnhancedInputComponent>(InputComponent);
	// check f will crash the game and output an error if the first argument is invalid 
	checkf(inputComponentPtr, TEXT("Unable to get a reference to UEnhancedInputComponent"));
	// get a reference to the player character (pawn)
	playerPtr = Cast<ACharacter>(pawn);
	checkf(playerPtr, TEXT("Unable to get a reference to player"));

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("Unable to get a reference to UEnhancedInputLocalPlayerSubsystem."));

	inputSubsystem->AddMappingContext(inputMappingContext, 0);

	// bind the input actions
	inputComponentPtr->BindAction(actionMove, ETriggerEvent::Triggered, this, &AMyPlayerController::HandleMoveInput);
	inputComponentPtr->BindAction(actionInteract, ETriggerEvent::Triggered, this, &AMyPlayerController::HandleInteractInput);
	}

 void AMyPlayerController::OnUnPossess()
 {
	 inputComponentPtr->ClearActionBindings();
	 Super::OnUnPossess();
 }

 void AMyPlayerController::HandleInteractInput()
 {

 }

 void AMyPlayerController::HandleMoveInput(const FInputActionValue& inputActionValue)
 {
	 //Unreal Engine classes use an F prefix for all their structures and classes.
	 const FVector2D movementVector = inputActionValue.Get<FVector2D>();
	 //execute movement. AddMovementInput is inhereted from 
	 playerPtr->AddMovementInput(playerPtr->GetActorForwardVector(), movementVector.X);
	 playerPtr->AddMovementInput(playerPtr->GetActorRightVector(), movementVector.Y);
 }
