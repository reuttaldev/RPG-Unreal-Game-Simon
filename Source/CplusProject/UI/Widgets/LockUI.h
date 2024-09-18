#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "../../Environment/LockControllerComponent.h"
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
	// ============================= FUNCTIONS =============================
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
	bool CheckSequence();
	void PlaySequence() const;
	void OpenLock();
	void SetLockController(ULockControllerComponent* newController);
protected:
	// ============================= FUNCTIONS =============================
	virtual void NativeConstruct() override;
private: 
	// ============================= PROPERTIES =============================
	UPROPERTY()
	// here is all the data we need to know about the mechanism of the lock that is currently open
	ULockControllerComponent* lockController = nullptr;
	UPROPERTY()
	UAudioComponent* audioComponent= nullptr;
	UPROPERTY()
	// to keep track of what the player has pressed so far
	TArray<Notes> sequence;
	// ============================= FUNCTIONS =============================
	bool ValidityChecks(ULockControllerComponent* newController) const;
	void PlaySound(int8 noteNumber);
	void ResetSequence();
	void AddToSequence(Notes note);
	void ShowWrongSequenceUI();
	void OnButtonClick(Notes note);
	void DebugSequences();

};