#include "FlickeringLight.h"
AFlickeringLight::AFlickeringLight()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
    // init settings
    timePassed= 0.0f;
    minIntensity = 100;
    maxIntensity = 200;
    flickerBreak = 0.2;
    // create component
    // Create a root components
    USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotlightComponent"));
    spotlight->SetupAttachment(root);
    spotlight->SetIntensity(minIntensity);
}
// Called every frame
void AFlickeringLight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // accumulate time
    timePassed += DeltaTime;
    if (timePassed >= flickerBreak)
        FlickerLight();
}

void AFlickeringLight::BeginPlay()
{
    Super::BeginPlay();
}

void AFlickeringLight::FlickerLight()
{
   // generate random intensity 
    float NewIntensity = FMath::FRandRange(minIntensity, maxIntensity);
    spotlight->SetIntensity(NewIntensity);
    timePassed = 0.0f;
}
