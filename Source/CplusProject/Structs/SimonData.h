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
	//UPROPERTY(EditAnywhere, Category = "Data")
};

// already exists
/*FORCEINLINE bool operator==(const TArray<Notes>& Array1, const TArray<Notes>& Array2)
{
	if (Array1.Num() != Array2.Num())
	{
		return false;
	}

	for (int32 i = 0; i < Array1.Num(); i++)
	{
		if (Array1[i] != Array2[i])
		{
			return false;
		}
	}

	return true;
}*/
