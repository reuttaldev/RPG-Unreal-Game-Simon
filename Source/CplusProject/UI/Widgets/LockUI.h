#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CplusProject/LockController.h"
#include "../../Structs/SimonData.h"
#include "Components/AudioComponent.h"
#include "LockUI.generated.h"

UCLASS()
class CPLUSPROJECT_API ULockUI : public UUserWidget
{
	GENERATED_BODY()
public:
	// ============================= PROPERTIES =============================
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UButton* redButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UButton* greenButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UButton* blueButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UButton* yellowButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UButton* hintButton;
	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> notesAudio;

	UPROPERTY(EditAnywhere)
	// using TSubclassOf and not pointers because I want to refer to an instance of a blueprint class of a type (these are considered Blueprint classes, not instances of a class for some reason), and not to a class object that was created at runtime
	// I will be instantiating it in begin play
	TSubclassOf<ALockController> initLockControllerClass;
	// ============================= FUNCTIONS =============================
	void SetLockController(TSubclassOf<ALockController> newClass, bool deletePrevious = true);
	UFUNCTION()
	void BindButtons();
	UFUNCTION()
	void RedButton();
	UFUNCTION()
	void BlueButton();
	UFUNCTION()
	void GreenButton();
	UFUNCTION()
	void YellowButton() ;
	UFUNCTION()
	void GiveHint();
	// returns true if the player was able to play the sequence that is set in the lock data
	bool CheckSequence(const TArray<Notes>& checkSequence) const;
	void PlaySequence() const;
	void OpenLock();
protected:
	// ============================= FUNCTIONS =============================
	virtual void NativeConstruct() override;
private: 
	// ============================= PROPERTIES =============================
	UPROPERTY()
	ALockController* lockController= nullptr;
	UPROPERTY()
	UAudioComponent* audioComponent= nullptr;
	// ============================= FUNCTIONS =============================
	void ValidityChecks();
	void PlaySound(int8 noteNumber);
	void ResetSequence();
	void AddToSequence(int8 noteNumber);
};
