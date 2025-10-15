#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController()
{
	canInteract = false;
	isInteracting = false;
}

void AMyPlayerController::SetLastInteractedActor(AActor* actor)
{
	if (!actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("bad actor pointer"));

	}
	lastInteractedActor = actor;
	UE_LOG(LogTemp, Warning, TEXT("Last Interacted Actor Name: %s"), *lastInteractedActor->GetName());
}

/// on enable and on disable. pawn = player. This gets called once the controller gets connected to the player that was spawned.
void AMyPlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	inputComponentPtr = Cast<UEnhancedInputComponent>(InputComponent);
	// check f will crash the game and output an error if the first argument is invalid 
	checkf(inputComponentPtr, TEXT("Unable to get UEnhancedInputComponent"));
	// get a reference to the player character (pawn)
	playerPtr = Cast<ACharacter>(pawn);
	checkf(playerPtr, TEXT("Unable to get player"));

	// get the collision component of the player 
	playerCollisionComponent = playerPtr->FindComponentByClass<UCapsuleComponent>();
	checkf(playerCollisionComponent, TEXT("Unable to player collision component"));
	// bind the collision to activate the overlap logic handling 
	playerCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayerController::OverlapBegin);
	playerCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AMyPlayerController::OverlapEnd);


	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("Unable to get UEnhancedInputLocalPlayerSubsystem."));

	inputSubsystem->AddMappingContext(inputMappingContext, 0);

	// bind the input actions
	inputComponentPtr->BindAction(actionMove, ETriggerEvent::Triggered, this, &AMyPlayerController::HandleMoveInput);
	inputComponentPtr->BindAction(actionInteract, ETriggerEvent::Started, this, &AMyPlayerController::HandleInteractInput);

	//  get a reference to the hud
	uiController = Cast<AGameUIContoller>(APlayerController::GetHUD());
	checkf(uiController, TEXT("Unable to get uiController"));

}

 void AMyPlayerController::OnUnPossess()
 {
	 inputComponentPtr->ClearActionBindings();
	 Super::OnUnPossess();
 }

 void AMyPlayerController::HandleMoveInput(const FInputActionValue& inputActionValue)
 {
	 //Unreal Engine classes use an F prefix for all their structures and classes.
	 const FVector2D movementVector = inputActionValue.Get<FVector2D>();
	 //execute movement.
	 playerPtr->AddMovementInput(playerPtr->GetActorForwardVector(), movementVector.X * movementSpeed* 100);
	 playerPtr->AddMovementInput(playerPtr->GetActorRightVector(), movementVector.Y * movementSpeed);
	 // this will be used in the animation
	 direction.X = movementVector.X;
	 direction.Y = -movementVector.Y;

 }

 void AMyPlayerController::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
	 if (!OtherActor || !OtherActor->GetClass())
	 {
		 UE_LOG(LogTemp, Warning, TEXT("Invalid OtherActor"));
		 return;
	 }
	 // check if the actor we hit implements the interaction interface.
	 // if it doesn't, we don't care about it. 
	 if (!OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		 return;
	 // cast OtherActor to the interface type 

	 IInteractionInterface* interfacePtr = Cast<IInteractionInterface>(OtherActor);
	 if (!interfacePtr->GetItemData().interactable)
		 return;
	 lastInteractedActor = OtherActor;
	 // show popup telling player they can interact with an item
	 if (!uiController)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("no UI controller on player controller"));
		 return;
	 }
	 uiController->OpenEncourageInteractUI();
	 // do some effect on the object e.g. highlight it 
	 interfacePtr->BeginFocus2D();
	 // enable interaction action
	 canInteract = true;
 }

 void AMyPlayerController::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
	 // close popup telling player they can interact with an item
	 if (!uiController)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("no UI controller on player controller"));
		 return;
	 }
	 uiController->CloseAll();
	 //disable effect on the object
     Cast<IInteractionInterface>(OtherActor)->EndFocus2D();
	 // disable interaction action
	 canInteract = false;
	 isInteracting = false;
	 lastInteractedActor = nullptr;
 }
 
 void AMyPlayerController::HandleInteractInput()
 {
	 if (!canInteract)
		 return; // we have nothing to interact with
	 if (!uiController)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("no UI controller on player controller"));
		 return;
	 }
	 if (!lastInteractedActor)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("no last interacted actor on player controller"));
		 return;
	 }
	 // if we press E while the panels are already open, close them
	 if (isInteracting)
	 {
		 uiController->CloseAll();
		 isInteracting = false;
		 return;
	 }
	 isInteracting = true;
	 // close popup
	 uiController->CloseEncourageInteractUI();
	 // open interaction panel with relevant text
	 uiController->UpdateInteractionUI(lastInteractedActor);
 }