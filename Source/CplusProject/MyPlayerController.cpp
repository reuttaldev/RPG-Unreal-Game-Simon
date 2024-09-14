#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

void AMyPlayerController::BeginPlay()
{

}

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

	//  get a reference to the hud
	uiController = Cast<AUIController>(APlayerController::GetHUD());
}

 void AMyPlayerController::OnUnPossess()
 {
	 inputComponentPtr->ClearActionBindings();
	 Super::OnUnPossess();
 }

 void AMyPlayerController::HandleInteractInput()
 {
	 if (!canInteract)
		 return; // we have nothing to interact with

	 if (isInteracting)
	 {
		 isInteracting = false;
		 lastHitActor = nullptr;
		 uiController->CloseUI();
	 }
	 checkf(lastHitActor, TEXT("CanInteract bool is set to true, but lastHutActor is nullptr"));
	 isInteracting = true;
	 uiController->CloseEncourageInteractUI();
	 uiController->UpdateInteractionUI(lastHitActor->GetItemData());
	 //lastHitActor->Interact();
 }

 void AMyPlayerController::HandleMoveInput(const FInputActionValue& inputActionValue)
 {
	 //Unreal Engine classes use an F prefix for all their structures and classes.
	 const FVector2D movementVector = inputActionValue.Get<FVector2D>();
	 //execute movement. AddMovementInput is inhereted from 
	 playerPtr->AddMovementInput(playerPtr->GetActorForwardVector(), movementVector.X);
	 playerPtr->AddMovementInput(playerPtr->GetActorRightVector(), movementVector.Y);
 }

 void AMyPlayerController::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
	 // check if the actor we hit implements the interaction interface.
	 // if it doesn't, we don't care about it. 
	 if (!OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		 return;

	 // set last hit actor to be what we collided with
	 // cast OtherActor to the interface type
	 IInteractionInterface* InterfacePtr = Cast<IInteractionInterface>(OtherActor);
	 // assign the casted pointer to the TScriptInterface
	 //lastHitActor = TScriptInterface<IInteractionInterface>(InterfacePtr);
	 //lastHitActor = Cast< IInteractionInterface>(OtherActor);

	 // show popup telling player they can interact with an item
	 uiController->UpdateInteractionUI(InterfacePtr->GetItemData());
	 // do some effect on the object e.g. highlight it 
	 InterfacePtr->BeginFocus2D();
	 // enable interaction action
	 canInteract = true;
 }

 void AMyPlayerController::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
	 // close popup telling player they can interact with an item
	 uiController->CloseUI();
	 //disable effect on the object
     Cast<IInteractionInterface>(OtherActor)->EndFocus2D();
	 // disable interaction action
	 canInteract = false;
	 lastHitActor = nullptr;
 }

