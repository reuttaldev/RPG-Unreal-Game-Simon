// Fill out your copyright notice in the Description page of Project Settings.


#include "LockTrigger.h"

// Sets default values
ALockTrigger::ALockTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALockTrigger::BeginPlay()
{

	Super::BeginPlay();
	
}

// Called every frame
void ALockTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALockTrigger::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ALockTrigger::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

