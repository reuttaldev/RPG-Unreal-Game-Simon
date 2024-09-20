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
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UImage* greenHighlightImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UImage* blueHighlightImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UImage* yellowHighlightImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI Binding")
	UImage* redHighlightImage;
	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> notesAudio;
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* errorSound;
	UPROPERTY(EditAnywhere, Category = "Visuals")
	float timeBetweenNotes = 0.7f;
	UPROPERTY(EditAnywhere, Category = "Visuals")
	float showButtonHightlightTime = 0.7f;
	UPROPERTY(EditAnywhere, Category = "Visuals")
	float showErrorTime = 1.3f;
	UPROPERTY(EditAnywhere, Category = "Audio")
	float volumeMultiplier = 1.5;
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
	/// when the UI panel gets opened
	void OnOpen();
	UFUNCTION()
	/// when the player successfully repeated the sequence
	void OnUnlocked();
	UFUNCTION()
	/// when the UI panel gets closed
	void OnClose();
	UFUNCTION()
	void PlaySequence();
	/// returns true if the player was able to play the sequence that is set in the lock data
	bool CheckSequence();
	void SetLockController(ULockControllerComponent* newController);
protected:
	// ============================= FUNCTIONS =============================
	virtual void NativeConstruct() override;
private: 
	// ============================= PROPERTIES =============================
	UPROPERTY()
	/// here is all the data we need to know about the mechanism of the lock that is currently open
	ULockControllerComponent* lockController = nullptr;
	UPROPERTY()
	UAudioComponent* audioComponent= nullptr;
	UPROPERTY()
	/// to keep track of what the player has pressed so far
	TArray<Notes> sequence;
	UPROPERTY()
	class AGameUIContoller* uiController; // circular dependencies
	FTimerHandle imageTimerHandle;
	FTimerHandle playTimerHandle;
	FTimerDelegate playNoteDelegate;
	// ============================= FUNCTIONS =============================
	bool ValidityChecks(const ULockControllerComponent* newController) const;
	void PlayNote(int8 noteNumber);
	void ResetSequence();
	void AddToSequence(Notes note);
	void ShowWrongSequenceUI();
	void OnButtonClick(ButtonColors color);
	void DebugSequences();
	void ShowImage( UImage* image, bool hideAutomatically = true, float delay = 0.5f);
	void HideImage( UImage* image);
	void PlayNextSound(int i);
	void ShowHighlightEffect(ButtonColors color);
	void HideHightlightEffect();
	ButtonColors FindColorByNote(Notes note) const;
};