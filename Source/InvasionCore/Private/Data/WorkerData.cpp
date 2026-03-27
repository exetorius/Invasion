#include "Data/WorkerData.h"
#include "Net/UnrealNetwork.h"

UWorkerData::UWorkerData()
{
	UniqueID = FGuid::NewGuid();
}

void UWorkerData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Identity
	DOREPLIFETIME(UWorkerData, UniqueID);
	DOREPLIFETIME(UWorkerData, Name);
	DOREPLIFETIME(UWorkerData, Race);
	DOREPLIFETIME(UWorkerData, Role);
	
	//Combat Stats
	DOREPLIFETIME(UWorkerData, Health);
	DOREPLIFETIME(UWorkerData, MaxHealth);
	DOREPLIFETIME(UWorkerData, CombatSkill);
	
	// Work Stats
	DOREPLIFETIME(UWorkerData, WorkEfficiency);
	
	// State
	DOREPLIFETIME(UWorkerData, Morale);
	DOREPLIFETIME(UWorkerData, InjurySeverity);
	DOREPLIFETIME(UWorkerData, bIsDead);
	DOREPLIFETIME(UWorkerData, CurrentStatus);
}

TObjectPtr<UWorkerData> UWorkerData::CreateWorker(UObject* Outer, EWorkerRole InRole, EWorkerRace InRace)
{
	UWorkerData* Worker = NewObject<UWorkerData>(Outer);
	if (!Worker)
	{
		UE_LOG(LogTemp, Warning, TEXT("WorkerData: Failed to generate worker"));
		return nullptr;
	}
	
	Worker->Role = InRole;
	Worker->Race = InRace;
	return Worker;
}

// --- HEALTH ---

void UWorkerData::AddHealth(float HealthToAdd)
{
	Health = FMath::Min(Health + HealthToAdd, MaxHealth);
}

void UWorkerData::RemoveHealth(float HealthToRemove)
{
	Health = FMath::Max(Health - HealthToRemove, 0.f);
}

void UWorkerData::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
}

// --- MAX HEALTH ---

void UWorkerData::AddMaxHealth(float MaxHealthToAdd)
{
	MaxHealth = FMath::Min(MaxHealth + MaxHealthToAdd, 100.f);
}

void UWorkerData::RemoveMaxHealth(float MaxHealthToRemove)
{
	const float Floor = MaxHealth / 2.f;
	MaxHealth = FMath::Max(MaxHealth - MaxHealthToRemove, Floor);
}

void UWorkerData::SetMaxHealth(float NewMaxHealth)
{
	const float Floor = MaxHealth / 2.f;
	MaxHealth = FMath::Clamp(NewMaxHealth, Floor, 100.f);
}

// --- MORALE ---

void UWorkerData::AddMorale(float MoraleToAdd)
{
	Morale = FMath::Clamp(Morale + MoraleToAdd, 0.f, 100.f);
}

void UWorkerData::RemoveMorale(float MoraleToRemove)
{
	Morale = FMath::Clamp(Morale - MoraleToRemove, 0.f, 100.f);
}

void UWorkerData::SetMorale(float NewMorale)
{
	Morale = FMath::Clamp(NewMorale, 0.f, 100.f);
}
