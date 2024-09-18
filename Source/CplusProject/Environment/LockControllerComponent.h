#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Structs/SimonData.h"
#include "LockControllerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPLUSPROJECT_API ULockControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULockControllerComponent();
	// these memebers must be public, otherwise I cannot change the values in the editor, which would deify the whole point 
	UPROPERTY(EditAnywhere, Category = "Lock Data")
	FSimonData simonData;
	UPROPERTY(EditAnywhere, Category = "Lock Data")
	FString nextLevelName;
protected:
	virtual void BeginPlay() override;
public:

};
