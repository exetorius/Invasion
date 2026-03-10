// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "PlayerUnit.generated.h"

class ATurnManager;

UCLASS()
class INVASIONTACTICAL_API APlayerUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	APlayerUnit();
	virtual void OnTurnStart() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	// TODO: Temp debug input — RequestEndTurn moves to PlayerController when #38 (End Turn button) is wired
	UPROPERTY()
	TObjectPtr<ATurnManager> TurnManager;
	
	bool bEndTurnKeyWasDown = false;
	
};
