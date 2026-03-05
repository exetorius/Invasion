// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "EnemyUnit.generated.h"

UCLASS()
class INVASIONTACTICAL_API AEnemyUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	AEnemyUnit();
	virtual void OnTurnStart() override;

};
