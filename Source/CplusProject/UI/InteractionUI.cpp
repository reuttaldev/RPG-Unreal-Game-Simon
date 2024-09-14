// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionUI.h"

void UInteractionUI::UpdateWidget(const FText& data) const
{
	textBlock->SetText(data);
}
