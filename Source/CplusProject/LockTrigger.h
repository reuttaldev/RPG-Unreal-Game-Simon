// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockController.h"
#include "AInteractableActor.h"
#include "Components/BoxComponent.h"
#include "LockTrigger.generated.h"

UCLASS()
class CPLUSPROJECT_API ALockTrigger : public AAInteractableActor
{

	GENERATED_BODY()
	
public:	
	// ============================= FUNCTIONS =============================
	ALockTrigger();
	// ============================= PROPERTIES =============================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALockController* controller=nullptr;
};
