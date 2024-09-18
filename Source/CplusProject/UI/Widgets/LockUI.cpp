#include "LockUI.h"
#include "Kismet/GameplayStatics.h"


void ULockUI::NativeConstruct()
{
	Super::NativeConstruct();
	audioComponent = NewObject<UAudioComponent>(this);
	audioComponent->RegisterComponentWithWorld(GetWorld());
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
	if (newController->simonData.sequence.Num() < 4)
	{
		UE_LOG(LogTemp, Error, TEXT("sequence array has fewer than 4 elements."));
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
	hintButton->OnClicked.AddDynamic(this, &ULockUI::GiveHint);
	redButton->OnClicked.AddDynamic(this, &ULockUI::RedButton);
	blueButton->OnClicked.AddDynamic(this, &ULockUI::BlueButton);
	greenButton->OnClicked.AddDynamic(this, &ULockUI::GreenButton);
	yellowButton->OnClicked.AddDynamic(this, &ULockUI::YellowButton);
}

void ULockUI::PlaySound(int8 noteNumber)
{
	audioComponent->SetSound(notesAudio[noteNumber+1]);
	audioComponent->Play();
}
void ULockUI::OnButtonClick(Notes note)
{
	PlaySound((uint8)note);
	AddToSequence(note);
	bool success = CheckSequence();
	UE_LOG(LogTemp, Warning, TEXT("Success is %s"), success ? TEXT("true") : TEXT("false"));
	if (success)
	{
		OpenLock();
		UE_LOG(LogTemp, Warning, TEXT("Opening Lock"));
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

void ULockUI::GiveHint()
{
}

bool ULockUI::CheckSequence()
{
	UE_LOG(LogTemp, Warning, TEXT("len is: %d"), sequence.Num());
	if(sequence.Num() < lockController->simonData.sequence.Num())
		return false;
	if (sequence.Num() > lockController->simonData.sequence.Num())
	{
		ResetSequence();
		ShowWrongSequenceUI();
		return false;
	}
	DebugSequences();
	return sequence == lockController->simonData.sequence;
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
void ULockUI::PlaySequence() const
{
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
	ResetSequence();
}

void ULockUI::OpenLock()
{

}

