// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyController.h"


void AKeyController::AddKey(FString doorName)
{
	if (!HasKey(doorName))
	{
		inventory.Add(doorName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to add a key which is already in the inventory"));
	}
	OnKeyAdded.Broadcast(doorName);
}

void AKeyController::RemoveKey(FString doorName)
{
}

bool AKeyController::HasKey(FString doorName)
{
	return inventory.Contains(doorName);
}
