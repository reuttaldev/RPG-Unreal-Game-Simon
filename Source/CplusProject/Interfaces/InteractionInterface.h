// Unlike C++, in unreal you do NOT have to implement all functions in order to implement an interface. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Structs/ItemData.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *  Every object that the player can interact with must implement this interface. 
 */
class CPLUSPROJECT_API IInteractionInterface
{
	GENERATED_BODY()
public:
	// ============================= FUNCTIONS =============================
	virtual void BeginFocus2D()=0;
	virtual void EndFocus2D() = 0;
	virtual const FItemData& GetItemData() const = 0;
};
