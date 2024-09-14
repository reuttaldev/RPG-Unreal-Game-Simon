// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionUI.h"

void UInteractionUI::UpdateWidget(const FString& data)
{
	textBlock->SetText(FText::FromString(data));
}
