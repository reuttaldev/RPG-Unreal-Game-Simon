#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "KeyController.generated.h"

// declare a delegate. From this I will create actions that will envoke when inventory events occure. 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryAction, const FString&, itemName);

UCLASS()
class CPLUSPROJECT_API AKeyController: public AActor
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddKey(FString doorName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveKey(FString doorName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasKey(FString doorName);
	//BlueprintAssignable: Allows Blueprints to bind custom events to delegates.
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryAction OnKeyAdded;

private: 
	TArray<FString> inventory;

};

