#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"  
UENUM()
enum class ItemType
{
	Interactable,
	Static,
	Lock,
	// for further development use
	NPC,
	Pickup
};

USTRUCT()
struct CPLUSPROJECT_API FItemData
{
	GENERATED_BODY();
	FItemData();
	UPROPERTY(EditInstanceOnly) // each instance will have its own copy of an ItemData
	ItemType itemType;
	UPROPERTY(EditInstanceOnly)
	FText description;
};
