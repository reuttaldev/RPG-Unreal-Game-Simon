#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/SimonData.h"
#include "LockController.generated.h"

UCLASS()
class CPLUSPROJECT_API ALockController : public AActor
{
	GENERATED_BODY()
	
public:	
	// ============================= FUNCTIONS =============================
	ALockController();
	// ============================= PROPERTIES =============================

	UPROPERTY(EditAnywhere, Category = "Data")
	FSimonData simonData;
	UPROPERTY(EditAnywhere, Category = "Data")
	FString nextLevelName;

protected:
	virtual void BeginPlay() override;

private:

};
