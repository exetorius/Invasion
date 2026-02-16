#pragma once

#include "WorkerTypes.generated.h"

UENUM(BlueprintType)
enum class EWorkerRace : uint8
{
	EWR_Unknown		UMETA(DisplayName = "Unknown"),
	EWR_Human		UMETA(DisplayName = "Human"),

	EWR_DefaultMAX	UMETA(DisplayName = "MAX")
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

UENUM(BlueprintType)
enum class EWorkerStatus: uint8
{
	EWS_Idle		UMETA(DisplayName = "Idle"),
	EWS_OnMission	UMETA(DisplayName = "On Mission"),
	EWS_Working		UMETA(DisplayName = "Working"),
	EWS_Injured		UMETA(DisplayName = "Injured"),
	
	EWS_DefaultMAX	UMETA(DisplayName = "MAX")
};
