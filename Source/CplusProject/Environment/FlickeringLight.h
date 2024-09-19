#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "FlickeringLight.generated.h"

UCLASS()
class CPLUSPROJECT_API AFlickeringLight : public AActor
{
	GENERATED_BODY()
	
public:	
    // ============================= FUNCTIONS =============================
	AFlickeringLight();
 	virtual void Tick(float DeltaTime) override;
    // ============================= PROPERTIES =============================
    UPROPERTY(EditAnywhere, Category = "Light Control")
    USpotLightComponent* spotlight;
protected:
    virtual void BeginPlay() override;
private:
    // ============================= PROPERTIES =============================
    UPROPERTY(EditAnywhere, Category = "Flicker Settings")
    float minIntensity;

    UPROPERTY(EditAnywhere, Category = "Flicker Settings")
    float maxIntensity;

    UPROPERTY(EditAnywhere, Category = "Flicker Settings")
    float flickerBreak;
    ///timer 
    float timePassed;
    // ============================= FUNCTIONS =============================
    void FlickerLight();

};
