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

	EWRO_MAX
};

UENUM()
enum class EWorkerStatus: uint8
{
	EWS_Idle,
	EWS_OnMission,
	EWS_Working,
	EWS_Injured,
	
	EWS_MAX
};

UENUM()
enum class EWorkerInjurySeverity : uint8
{
	EWIS_None,
	EWIS_Minor,
	EWIS_Major,
	EWIS_Critical,
	
	EWIS_MAX
};
