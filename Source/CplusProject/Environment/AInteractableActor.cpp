#include "AInteractableActor.h"

AAInteractableActor::AAInteractableActor()
{
}
void AAInteractableActor::BeginFocus2D()
{
	if (!itemData.interactable)
		return;
	UE_LOG(LogTemp, Warning, TEXT("BeginFocus"));
}
void AAInteractableActor::EndFocus2D()
{
	if (!itemData.interactable)
		return;
}

