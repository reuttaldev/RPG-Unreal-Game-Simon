#include "LockUI.h"
#include "Kismet/GameplayStatics.h"
#include "../Controllers/GameUIContoller.h"
#include "CplusProject/Environment/DoorOpenComponent.h"
#include "CplusProject/Player/MyPlayerController.h"

void ULockUI::NativeConstruct()
{
	Super::NativeConstruct();

	audioComponent = NewObject<UAudioComponent>(this);
	audioComponent->RegisterComponentWithWorld(GetWorld());
	audioComponent->SetVolumeMultiplier(volumeMultiplier);

	uiController= Cast<AGameUIContoller>(GetWorld()->GetFirstPlayerController()->GetHUD());

	hintButton->OnClicked.AddDynamic(this, &ULockUI::PlaySequence);
	closeButton->OnClicked.AddDynamic(this, &ULockUI::CloseLockUI);

	HideErrorImage();
}
void ULockUI::SetLockController(ULockControllerComponent* newController)
{
	if (!ValidityChecks(newController))
		return;
	lockController = newController;
	BindButtons();
}

bool ULockUI::ValidityChecks(ULockControllerComponent* newController) const 
{
	if (!newController)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to update lock component but got nullptr."));
		return false;
	}
	if (newController->simonData.sequence.Num() ==0 )
	{
		UE_LOG(LogTemp, Error, TEXT("sequence array is empty."));
		return false;
	}
	if (newController->nextLevelName.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("next level name is empty on lock controller"));
		return false;
	}
	return true;
}

void ULockUI::BindButtons()
{
	redButton->OnClicked.AddDynamic(this, &ULockUI::RedButton);
	blueButton->OnClicked.AddDynamic(this, &ULockUI::BlueButton);
	greenButton->OnClicked.AddDynamic(this, &ULockUI::GreenButton);
	yellowButton->OnClicked.AddDynamic(this, &ULockUI::YellowButton);
}

void ULockUI::PlayNote(int8 noteNumber)
{
	audioComponent->SetSound(notesAudio[noteNumber+1]);
	audioComponent->Play();
}
void ULockUI::OnButtonClick(Notes note)
{
	PlayNote((uint8)note);
	AddToSequence(note);
	bool success = CheckSequence();
	if (success)
	{
		OpenLock();
	}
}

void ULockUI::RedButton()
{
	OnButtonClick(lockController->simonData.redNote);
}

void ULockUI::BlueButton()
{
	OnButtonClick(lockController->simonData.blueNote);
}

void ULockUI::GreenButton()
{
	OnButtonClick(lockController->simonData.greenNote);
}

void ULockUI::YellowButton()
{
	OnButtonClick(lockController->simonData.yellowNote);
}

void ULockUI::CloseLockUI()
{
	if (!uiController)
		uiController = Cast<AGameUIContoller>(GetWorld()->GetFirstPlayerController()->GetHUD());

	checkf(uiController, TEXT("LockUI could not get a reference to GameUIController, or it was lost "));
	uiController->CloseLockUI();
}

bool ULockUI::CheckSequence()
{
	if (sequence.Num() < lockController->simonData.sequence.Num())
		return false;
	if (sequence == lockController->simonData.sequence)
		return true;
	// array is bigger, or equal but not the correct sequence 
	ResetSequence();
	ShowWrongSequenceUI();
	return false;
	;
}

void ULockUI::DebugSequences()
{
	UE_LOG(LogTemp, Warning, TEXT("Array1 Contents:"));
	for (Notes note : lockController->simonData.sequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), (int8)note);
	}

	UE_LOG(LogTemp, Warning, TEXT("Array2 Contents:"));
	for (Notes note : sequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), (int8)note);
	}
}
void ULockUI::PlaySequence() 
{
	PlayNextSound(-1);
}
void ULockUI::ResetSequence()
{
	sequence.Reset();
}

void ULockUI::AddToSequence(Notes note)
{
	sequence.Add(note);
}

void ULockUI::ShowWrongSequenceUI()
{
	audioComponent->SetSound(errorSound);
	audioComponent->Play();
	ShowErrorImage();
	GetWorld()->GetTimerManager().SetTimer(flashTimerHandle, this, &ULockUI::HideErrorImage, timeBetweenNotes, false);
}

void ULockUI::OpenLock()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening Lock"));
	// generate an open door class instance in the exact same the locked door was before
	// the open door class inherits from intractable actor, so player can leave the room

	FVector loc = lockController->GetOwner()->GetActorLocation();
	FRotator rot = lockController->GetOwner()->GetActorRotation();
	FString sceneName = lockController->nextLevelName;
	// destroy it since we left the lock and it is no longer relevant
	lockController->GetOwner()->Destroy();
	lockController = nullptr;

	AAInteractableActor* newActor = GetWorld()->SpawnActor<AAInteractableActor>(openDoorActorClass, loc, rot);
	// get the scene name that was set on the lock controller, which says which scene should be loaded once the lock is open
	newActor->FindComponentByClass<UDoorOpenComponent>()->SetSceneName(sceneName);

	// tell the UI panel this data is what it needs to interact with now 
	Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->SetLastInteractedActor(newActor);
	CloseLockUI(); 
}
void ULockUI::ShowErrorImage()
{
	errorImage	->SetVisibility(ESlateVisibility::Visible);
}
void ULockUI::HideErrorImage()
{
	errorImage	->SetVisibility(ESlateVisibility::Collapsed);
}

void ULockUI::PlayNextSound(int i)
{
	i++;
	if (i >= lockController->simonData.sequence.Num())
	{
		return; 
	}
	UE_LOG(LogTemp, Warning, TEXT("playing index %d"), (int8)i);
	PlayNote((int8)lockController->simonData.sequence[i]);
	audioComponent->Play();	
	playNoteDelegate.BindUObject(this, &ULockUI::PlayNextSound, i);
	GetWorld()->GetTimerManager().SetTimer(playTimerHandle, playNoteDelegate, timeBetweenNotes, false);
}