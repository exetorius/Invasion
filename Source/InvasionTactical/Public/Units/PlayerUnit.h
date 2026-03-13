// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "PlayerUnit.generated.h"


UCLASS()
class INVASIONTACTICAL_API APlayerUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	APlayerUnit();
	virtual void OnTurnStart() override;
	
	void MoveToTile(ATacticalGridTile* MoveTile);

protected:
	virtual void BeginPlay() override;

};
