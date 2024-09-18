#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "../../Environment/LockControllerComponent.h"
#include "../../Environment/AInteractableActor.h"
#include "../../Structs/SimonData.h"
#include "Components/AudioComponent.h"
#include "Components/Image.h"
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
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UButton* closeButton;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UImage* errorImage;
	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> notesAudio;
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* errorSound;
	UPROPERTY(EditAnywhere, Category = "Audio")
	float timeBetweenNotes = 0.7f;
	UPROPERTY(EditAnywhere, Category = "Audio")
	float volumeMultiplier = 2;
	// ============================= PROPERTIES =============================
	UPROPERTY(EditAnywhere, Category = "Panels")
	TSubclassOf<AAInteractableActor> openDoorActorClass;
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
	void CloseLockUI();
	UFUNCTION()
	void PlaySequence();
	// returns true if the player was able to play the sequence that is set in the lock data
	bool CheckSequence();
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
	UPROPERTY()
	class AGameUIContoller* uiController; // circular dependencies
	FTimerHandle flashTimerHandle;
	FTimerHandle playTimerHandle;
	FTimerDelegate playNoteDelegate;
	// ============================= FUNCTIONS =============================
	bool ValidityChecks(ULockControllerComponent* newController) const;
	void PlayNote(int8 noteNumber);
	void ResetSequence();
	void AddToSequence(Notes note);
	void ShowWrongSequenceUI();
	void OnButtonClick(Notes note);
	void DebugSequences();
	void ShowErrorImage();
	void HideErrorImage();
	void PlayNextSound(int i);
};