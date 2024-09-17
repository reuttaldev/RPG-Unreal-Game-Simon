#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockController.generated.h"

UCLASS()
class CPLUSPROJECT_API ALockController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockController();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	FString doorName; 
	UPROPERTY(EditAnywhere)
	FString nextLevelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
