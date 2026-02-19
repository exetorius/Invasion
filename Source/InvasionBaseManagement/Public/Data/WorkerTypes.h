#pragma once

UENUM()
enum class EWorkerRace : uint8
{
	EWR_Unknown,
	EWR_Human,	

	EWR_MAX	
};

UENUM()
enum class EWorkerRole : uint8
{
	EWRO_None,
	EWRO_Soldier,
	EWRO_Scientist,
	EWRO_Engineer,
	EWRO_Medic,
	EWRO_Pilot,

	EWRO_MAX	UMETA(DisplayName = "MAX")
};

UENUM()
enum class EWorkerStatus: uint8
{
	EWS_Idle,
	EWS_OnMission,
	EWS_Working,
	EWS_Injured,
	
	EWS_MAX	UMETA(DisplayName = "MAX")
};
