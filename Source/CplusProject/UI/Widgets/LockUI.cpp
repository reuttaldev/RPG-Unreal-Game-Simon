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

	BindButtons();

	HideImage(errorImage);
	HideHightlightEffect();
}

void ULockUI::SetLockController(ULockControllerComponent* newController)
{
	if (!ValidityChecks(newController))
		return;
	lockController = newController;
}

bool ULockUI::ValidityChecks(const ULockControllerComponent* newController) const 
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
	if (newController->simonData.mapColorToNote.Num() != 4)
	{
		UE_LOG(LogTemp, Error, TEXT("map color to note is not defined correctly"));
		return false;
	}
	return true;
}

void ULockUI::BindButtons()
{
	hintButton->OnClicked.AddDynamic(this, &ULockUI::PlaySequence);
	closeButton->OnClicked.AddDynamic(this, &ULockUI::OnClose);

	redButton->OnClicked.AddDynamic(this, &ULockUI::RedButton);
	blueButton->OnClicked.AddDynamic(this, &ULockUI::BlueButton);
	greenButton->OnClicked.AddDynamic(this, &ULockUI::GreenButton);
	yellowButton->OnClicked.AddDynamic(this, &ULockUI::YellowButton);
}

void ULockUI::PlayNote(const int8 noteNumber)
{
	audioComponent->SetSound(notesAudio[noteNumber+1]);
	audioComponent->Play();
}
void ULockUI::ShowHighlightEffect(const ButtonColors color)
{
	switch (color)
	{
	case ButtonColors::Yellow:

		ShowImage(yellowHighlightImage, true, showButtonHightlightTime);
		break;
	case ButtonColors::Red:

		ShowImage(redHighlightImage, true, showButtonHightlightTime);
		break;
	case ButtonColors::Green:

		ShowImage(greenHighlightImage, true, showButtonHightlightTime);
		break;
	case ButtonColors::Blue:

		ShowImage(blueHighlightImage, true, showButtonHightlightTime);
		break;
	}
}
void ULockUI::HideHightlightEffect()
{
	HideImage(redHighlightImage);
	HideImage(blueHighlightImage);
	HideImage(yellowHighlightImage);
	HideImage(greenHighlightImage);
}
void ULockUI::OnButtonClick(ButtonColors color)
{
	Notes noteToPlay = lockController->simonData.mapColorToNote[color];
	PlayNote((uint8)noteToPlay);
	ShowHighlightEffect(color);
	AddToSequence(noteToPlay);
	bool success = CheckSequence();
	if (success)
	{
		OnUnlocked();
	}
}

void ULockUI::RedButton()
{
	OnButtonClick(ButtonColors::Red);
}

void ULockUI::BlueButton()
{
	OnButtonClick(ButtonColors::Blue);
}

void ULockUI::GreenButton()
{
	OnButtonClick(ButtonColors::Green);
}

void ULockUI::YellowButton()
{
	OnButtonClick(ButtonColors::Yellow);
}
void ULockUI::OnOpen()
{
	if (!ValidityChecks(lockController))
		return; 
	PlaySequence();
}
void ULockUI::OnClose()
{
	lockController = nullptr;
	ResetSequence();
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
	/// array is bigger, or equal but not the correct sequence 
	ResetSequence();
	ShowWrongSequenceUI();
	return false;
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
void ULockUI::ShowImage(UImage* image, bool hideAutomatically, float delay)
{
	image->SetVisibility(ESlateVisibility::Visible);
	if (!hideAutomatically)
		return; 

	GetWorld()->GetTimerManager().SetTimer(imageTimerHandle, 
		[this, image]()
		{
			this->HideImage(image);
		},
		delay, false);
}
void ULockUI::HideImage(UImage* image) 
{
	image->SetVisibility(ESlateVisibility::Collapsed);
}
void ULockUI::PlaySequence() 
{
	UE_LOG(LogTemp, Warning, TEXT("playing sequence"));

	PlayNextSound(-1);
}
void ULockUI::ResetSequence()
{
	sequence.Reset();
	HideHightlightEffect();
}

void ULockUI::AddToSequence(Notes note)
{
	sequence.Add(note);
}

void ULockUI::ShowWrongSequenceUI()
{
	audioComponent->SetSound(errorSound);
	audioComponent->Play();
	ShowImage(errorImage,true, showErrorTime);
}

/// generate an open door class instance in the exact same the locked door was before
/// the open door class inherits from intractable actor, so player can leave the room
void ULockUI::OnUnlocked()
{

	FVector loc = lockController->GetOwner()->GetActorLocation();
	FRotator rot = lockController->GetOwner()->GetActorRotation();
	FString sceneName = lockController->nextLevelName;
	/// destroy it since we left the lock and it is no longer relevant
	lockController->GetOwner()->Destroy();
	lockController = nullptr;

	AAInteractableActor* newActor = GetWorld()->SpawnActor<AAInteractableActor>(openDoorActorClass, loc, rot);
	/// get the scene name that was set on the lock controller, which says which scene should be loaded once the lock is open
	newActor->FindComponentByClass<UDoorOpenComponent>()->SetSceneName(sceneName);

	/// tell the UI panel this data is what it needs to interact with now 
	Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->SetLastInteractedActor(newActor);
	OnClose(); 
}
ButtonColors ULockUI::FindColorByNote(Notes note) const
{
	for (const TPair<ButtonColors, Notes>& pair : lockController->simonData.mapColorToNote)
	{
		if (pair.Value == note)
		{
			return pair.Key;
		}
	}
	return ButtonColors::None;
}
void ULockUI::PlayNextSound(int i)
{
	i++;
	// recursion base case
	if (i >= lockController->simonData.sequence.Num())
	{
		return; 
	}

	Notes noteToPlay = lockController->simonData.sequence[i];
	// find which button color we need, based on the key we need to play and the map we have
	ButtonColors colorToShow = FindColorByNote(noteToPlay);
	if (colorToShow == ButtonColors::None)
	{
		UE_LOG(LogTemp, Error, TEXT("Note %d does not have a button color, could not display highlight"), (int8)noteToPlay);
		return;
	}
	ShowHighlightEffect(colorToShow);
	PlayNote((int8)noteToPlay);
	audioComponent->Play();	
	playNoteDelegate.BindUObject(this, &ULockUI::PlayNextSound, i);
	GetWorld()->GetTimerManager().SetTimer(playTimerHandle, playNoteDelegate, timeBetweenNotes, false);
}