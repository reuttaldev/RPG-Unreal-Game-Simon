// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractionInterface.h"
#include "AInteractableActor.generated.h"

UCLASS()
class CPLUSPROJECT_API AAInteractableActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
 	// ============================= FUNCTIONS =============================
	AAInteractableActor();
	virtual void BeginFocus2D() override;
	virtual void EndFocus2D() override;
	virtual const FItemData& GetItemData() const override{ return itemData; };
	// ============================= PROPERTIES =============================
	UPROPERTY(editanywhere)
	// public bc need to set in editor
	FItemData itemData;
};
