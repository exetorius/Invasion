// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "PathfinderTest.generated.h"

class ABaseUnit;

UCLASS()
class INVASIONTACTICAL_API APathfinderTest : public AActor
{
	GENERATED_BODY()

public:
	APathfinderTest();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	class ACombatManager* CombatManager;	
	
	UPROPERTY(VisibleInstanceOnly)
	int32 ShotCount = 0;
	UFUNCTION()
	void FireTestShot();
	
	ABaseUnit* Attacker;
	ABaseUnit* Defender;
	
	UPROPERTY(EditAnywhere)
	ECoverType CoverType = ECoverType::None;
	UPROPERTY(EditAnywhere)
	bool bIsFlanking = false;
	
	FTimerHandle ShotTimerHandle;
	

};
