#pragma once

UENUM(BlueprintType)
enum class EWorkerRace : uint8
{
	Unknown,
	Human,	

	Max	
};

UENUM(BlueprintType)
enum class EWorkerRole : uint8
{
	None,
	Soldier,
	Scientist,
	Engineer,
	Medic,
	Pilot,

	Max
};

UENUM(BlueprintType)
enum class EWorkerStatus: uint8
{
	Idle,
	OnMission,
	Working,
	Injured,
	
	Max
};

UENUM(BlueprintType)
enum class EInjurySeverity : uint8
{
	None,
	Minor,
	Major,
	Critical,
	
	Max
};

UENUM(BlueprintType)
enum class EUnitRank : uint8
{
	Rookie,
	Veteran,
	Elite,
	
	Max
};
