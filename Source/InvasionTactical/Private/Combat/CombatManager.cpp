// CopyrightNotice


#include "Combat/CombatManager.h"

#include "Units/BaseUnit.h"


ACombatManager::ACombatManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

FCombatHitResult ACombatManager::ResolveHit(ABaseUnit* Attacker, ABaseUnit* Defender, ECoverType Cover, bool bFlanking)
{
	int32 BaseHitChance = Attacker->GetCombatSkill();
	float DamageModifier = 1.f;
	
	FCombatHitResult CombatResult;

	switch (Cover)
	{
	case ECoverType::Full:
		BaseHitChance = BaseHitChance * 0.75f;
		DamageModifier = 0.75f;
		break;
	case ECoverType::Half:
		BaseHitChance = BaseHitChance * 0.9f;
		DamageModifier = 0.9f;
		break;
	case ECoverType::None:
		if (bFlanking)
		{
			BaseHitChance = BaseHitChance * 1.25f;			
		}
		break;
	}
	// So we cannot exceed 100 and guarantee a miss
	BaseHitChance = FMath::Clamp(BaseHitChance, 0, 100);
	
	// Score a hit
	if (FMath::RandRange(0, 100) <= BaseHitChance)
	{
		if (bFlanking && FMath::RandRange(0, 100) <= 50)
		{
			DamageModifier = 1.5f;
			CombatResult.bCrit = true;
		}
		constexpr int32 BaseDamage = 20;
		CombatResult.DamageDealt = BaseDamage * DamageModifier;
		CombatResult.bHit = true;		
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	  FString::Printf(TEXT("Hit: %s | Crit: %s | Damage: %.1f"),
		  CombatResult.bHit ? TEXT("Yes") : TEXT("No"),
		  CombatResult.bCrit ? TEXT("Yes") : TEXT("No"),
		  CombatResult.DamageDealt));
		
		Defender->RemoveHealth(CombatResult.DamageDealt);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Miss!"));
	}

	return CombatResult;
}

void ACombatManager::BeginPlay()
{
	Super::BeginPlay();
	
}

