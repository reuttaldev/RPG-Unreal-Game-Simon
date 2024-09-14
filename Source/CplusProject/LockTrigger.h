// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockController.h"
//#include "UI/UIController.h"
#include "Components/BoxComponent.h"
#include "LockTrigger.generated.h"

UCLASS()
class CPLUSPROJECT_API ALockTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALockController* controller=nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//AUIController* uiController = nullptr;
	ALockTrigger();
	virtual void Tick(float DeltaTime) override;
	//UFUNCTION(BlueprintCallable)
	//void OpenLockPanel();
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UBoxComponent* collisionBox;
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
