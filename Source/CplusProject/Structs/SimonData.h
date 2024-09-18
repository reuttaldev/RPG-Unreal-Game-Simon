#pragma once
#include "CoreMinimal.h"
#include "SimonData.generated.h"  

UENUM()
enum class Buttons : uint8
{
	Red,
	Green,
	Blue,
	Yellow
};
UENUM()
enum class Notes : uint8
{
	A,
	Ab,
	B,
	Bb,
	C,
	D,
	Db,
	E,
	Eb,
	F,
	G,
	Gb
};

USTRUCT()
struct CPLUSPROJECT_API FSimonData
{
	GENERATED_BODY();
public:
	FSimonData();

	// indicate which node will sound when a button is pressed
	// audios that should be heard when each button is pressed
	UPROPERTY(EditAnywhere, Category = "Notes")
	Notes redNote;
	UPROPERTY(EditAnywhere, Category = "Notes")
	Notes blueNote;
	UPROPERTY(EditAnywhere, Category = "Notes")
	Notes greenNote;
	UPROPERTY(EditAnywhere, Category = "Notes")
	Notes yellowNote;

	// the unique sequence of notes the device shall play
	UPROPERTY(EditAnywhere, Category = "Sequence")
	TArray<Notes> sequence;
};
