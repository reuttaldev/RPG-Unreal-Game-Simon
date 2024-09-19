#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DoorOpenComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSPROJECT_API UDoorOpenComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	UPROPERTY()
	/// the name of the scene we need to open when we interact with a open door class instance 
	FString nextScene;

public:
	inline void OpenDoor() 
	{
		if (nextScene.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("Trying to open door but next scene name is empty! DOorOpenCOmponent"));
			return;
		}
		UGameplayStatics::OpenLevel(GetWorld(), FName(nextScene));
	}
	inline void SetSceneName(const FString& sceneName) { nextScene = sceneName; }
		
};
