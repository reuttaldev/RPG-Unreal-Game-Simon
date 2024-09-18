#include "AInteractableActor.h"

AAInteractableActor::AAInteractableActor()
{
}
void AAInteractableActor::BeginFocus2D()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginFocus"));
}
void AAInteractableActor::EndFocus2D()
{
}

