#include "AInteractableActor.h"

AAInteractableActor::AAInteractableActor()
{
	// create the mesh and make it the parent
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mesh);
}
void AAInteractableActor::BeginFocus2D()
{
	// start a highlight effect
	mesh->SetRenderCustomDepth(true);
}
void AAInteractableActor::EndFocus2D()
{
	mesh->SetRenderCustomDepth(false);
}

void AAInteractableActor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting"));
}
