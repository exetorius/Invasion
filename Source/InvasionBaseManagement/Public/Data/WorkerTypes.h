#pragma once

UENUM()
enum class EWorkerRace : uint8
{
	EWR_Unknown,
	EWR_Human,	

	EWR_DefaultMAX	
};

UENUM()
enum class EWorkerRole : uint8
{
	EWR_None,
	EWR_Soldier,
	EWR_Scientist,
	EWR_Engineer,
	EWR_Medic,
	EWR_Pilot,

	EWR_DefaultMAX	UMETA(DisplayName = "MAX")
};

UENUM()
enum class EWorkerStatus: uint8
{
	EWS_Idle,
	EWS_OnMission,
	EWS_Working,
	EWS_Injured,
	
	EWS_DefaultMAX	UMETA(DisplayName = "MAX")
};
