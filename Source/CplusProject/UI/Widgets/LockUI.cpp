#include "LockUI.h"
#include "Kismet/GameplayStatics.h"


void ULockUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetLockController(initLockControllerClass,false);
	ValidityChecks();
	BindButtons();

	audioComponent = NewObject<UAudioComponent>(this);
	audioComponent->RegisterComponentWithWorld(GetWorld());
}
void ULockUI::SetLockController(TSubclassOf<ALockController> classType,bool deletePrevious)
{
	checkf(classType, TEXT("lock controller class set on lockUI is empty"));
	// if there is already something stored in lock controller
	if (lockController && deletePrevious)
	{
		// don't need to exactly manage the memory since it was created using New Object and unreal will do it for me,
		// but let's mark it explicitly for deletion 
		lockController->Destroy();
	}
	lockController = NewObject<ALockController>(classType);
}

void ULockUI::ValidityChecks()
{
	checkf(lockController, TEXT("lock controller is invalid"));
	checkf(lockController->simonData.sequence.Num()<4, TEXT("sequence array has fewer than 4 elements."));
	checkf(lockController->nextLevelName.IsEmpty(), TEXT("next level name is empty on lock controller"));
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
	UE_LOG(LogTemp, Warning, TEXT("The integer value of Note is: %d"), noteNumber);
	audioComponent->SetSound(notesAudio[noteNumber+1]);
	audioComponent->Play();
}

void ULockUI::ResetSequence()
{
}

void ULockUI::AddToSequence(int8 noteNumber)
{
}

void ULockUI::RedButton()
{
	PlaySound((uint8)lockController->simonData.redNote);
}

void ULockUI::BlueButton()
{
	PlaySound(static_cast<uint8>(lockController->simonData.blueNote));
}

void ULockUI::GreenButton()
{
	PlaySound(static_cast<uint8>(lockController->simonData.greenNote));
}

void ULockUI::YellowButton()
{
	PlaySound(static_cast<uint8>(lockController->simonData.yellowNote));
}

void ULockUI::GiveHint()
{
}

bool ULockUI::CheckSequence(const TArray<Notes>& checkSequence) const
{
	return false;
}

void ULockUI::PlaySequence() const
{
}

void ULockUI::OpenLock()
{
}
