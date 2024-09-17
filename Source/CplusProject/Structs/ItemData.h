#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"  
UENUM()
enum class ItemType : uint8
{
	Interactable ,
	Static,
	Lock,
	// for further development use
	NPC,
	Pickup,
};

USTRUCT()
struct CPLUSPROJECT_API FItemData
{
	GENERATED_BODY();
public:
	FItemData();
	UPROPERTY(editanywhere) // each instance will have its own copy of an ItemData
	ItemType itemType;
	UPROPERTY(editanywhere)
	FText description;
};
