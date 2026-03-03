// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TacticalGrid.generated.h"

UCLASS()
class INVASIONTACTICAL_API ATacticalGrid : public AActor
{
	GENERATED_BODY()

public:
	ATacticalGrid();

protected:
	virtual void BeginPlay() override;

};
