#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.generated.h"

UENUM(BlueprintType)
enum class ECardinalDirection : uint8
{
	North,
	East,
	South,
	West
};

UENUM(BlueprintType)
enum class ECoverType : uint8
{
	None,
	Half,
	Full
};

USTRUCT(BlueprintType)
struct FCoverData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECoverType North = ECoverType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECoverType East = ECoverType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECoverType South = ECoverType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECoverType West = ECoverType::None;
};

UENUM(BlueprintType)
enum class EFaction : uint8 
{
	None,
	Player,
	Enemy,
	CivilianFriendly,
	CivilianHostile
};

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	Healthy,
	Injured,
	Downed,
	Dead
};

UENUM(BlueprintType)
enum class ETacticalPhase : uint8
{
	Player,
	Enemy
};
