#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"  
UENUM()
enum class ItemType : uint8
{
	Interactable ,
	Static,
	Lock,
	OpenDoor,
	// for further development use
	NPC,
	Pickup,
};

USTRUCT()
	/// each intractable instance will have its own copy of an ItemData
struct CPLUSPROJECT_API FItemData
{
	GENERATED_BODY();
public:
	FItemData();
	UPROPERTY(editanywhere) 
	ItemType itemType;
	UPROPERTY(editanywhere)
	FText description;
	UPROPERTY(editanywhere)
	bool interactable;
};
