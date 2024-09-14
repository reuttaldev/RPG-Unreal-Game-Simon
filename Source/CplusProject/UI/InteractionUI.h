// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "InteractionUI.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSPROJECT_API UInteractionUI : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	void UpdateWidget(const FText& data) const;
private:
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	UTextBlock* textBlock;
};
