#pragma once

#include "WorkerTypes.generated.h"

UENUM(BlueprintType)
enum class ERace : uint8
{
	ER_Unknown		UMETA(DisplayName = "Unknown"),
	ER_Human		UMETA(DisplayName = "Human"),
	ER_Reptoid		UMETA(DisplayName = "Reptoid"),
	ER_Muton 		UMETA(DisplayName = "Muton"),
	ER_Sectoid		UMETA(DisplayName = "Sectoid"),
	ER_Android 		UMETA(DisplayName = "Android"),

	ER_DefaultMAX	UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class ESpecies : uint8
{
	ES_Undefined	UMETA(DisplayName = "Undefined"),
	ES_Terran		UMETA(DisplayName = "Terran"),
	ES_Alien		UMETA(DisplayName = "Alien"),
	ES_Robotic		UMETA(DisplayName = "Robotic"),

	ES_DefaultMAX	UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class EWorkerRole : uint8
{
	EWR_None		UMETA(DisplayName = "None"),
	EWR_Soldier		UMETA(DisplayName = "Soldier"),
	EWR_Scientist	UMETA(DisplayName = "Scientist"),
	EWR_Engineer    UMETA(DisplayName = "Engineer"),
	EWR_Medic		UMETA(DisplayName = "Medic"),
	EWR_Pilot		UMETA(DisplayName = "Pilot"),

	EWR_DefaultMAX	UMETA(DisplayName = "MAX")
};