// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "CombatManager.generated.h"

class ABaseUnit;

UCLASS()
class INVASIONTACTICAL_API ACombatManager : public AActor
{
	GENERATED_BODY()

public:
	ACombatManager();
	
	UFUNCTION(BlueprintCallable)
	FCombatHitResult ResolveHit (ABaseUnit* Attacker, ABaseUnit* Defender, ECoverType Cover, bool bFlanking);

};
