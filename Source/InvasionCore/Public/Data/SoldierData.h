// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "WorkerData.h"
#include "WorkerTypes.h"
#include "SoldierData.generated.h"

/**
 * 
 */
UCLASS()
class INVASIONCORE_API USoldierData : public UWorkerData
{
	GENERATED_BODY()
	
public:
	static TObjectPtr<USoldierData> CreateSoldier(UObject* Outer);
	
private:	
	UPROPERTY(Replicated)
	int32 KillCount = 0;
	UPROPERTY(Replicated)
	EUnitRank UnitRank = EUnitRank::Rookie;
	UPROPERTY(Replicated)
	EInjurySeverity InjurySeverity = EInjurySeverity::None;
	
	// Getters & setters
public:
	void AddKills(const int32 NewKillCount) { KillCount += NewKillCount; }
	UFUNCTION(BlueprintPure)
	int32 GetKillCount() const { return KillCount; }
	void SetUnitRank(const EUnitRank NewRank) { UnitRank = NewRank; }
	UFUNCTION(BlueprintPure)
	EUnitRank GetUnitRank() const { return UnitRank; }
	void SetInjurySeverity(const EInjurySeverity NewSeverity) { InjurySeverity = NewSeverity; }
	UFUNCTION(BlueprintPure)
	EInjurySeverity GetInjurySeverity() const { return InjurySeverity; }
};
