// CopyrightNotice


#include "PathfinderTest.h"

#include "Combat/CombatManager.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"


APathfinderTest::APathfinderTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APathfinderTest::BeginPlay()
{
	Super::BeginPlay();
	
	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));

	if (!ensure(CombatManager)) { return; }
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseUnit::StaticClass(), FoundActors);
	
	if (!ensure(FoundActors.Num() >= 2)) { return; }
	
	Attacker = Cast<ABaseUnit>(FoundActors[0]);
	Defender = Cast<ABaseUnit>(FoundActors[1]);
	
	ShotCount = 0;
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APathfinderTest::FireTestShot, .5f, true);	
}

void APathfinderTest::FireTestShot()
{	
	if (!ensure(CombatManager) || !ensure(Attacker) || !ensure(Defender))
	{
		 GetWorldTimerManager().ClearTimer(ShotTimerHandle);
		 return;
	}
	
	ShotCount++;
	FCombatHitResult Result = CombatManager->ResolveHit(Attacker, Defender, CoverType, bIsFlanking);
	
	FString ResultText;
	if (Result.bCrit)
	{
		ResultText = FString::Printf(TEXT("Shot %d: CRIT — Damage: %.1f"), ShotCount, Result.DamageDealt);
	}
	else if (Result.bHit)
	{
		ResultText = FString::Printf(TEXT("Shot %d: HIT — Damage: %.1f"), ShotCount, Result.DamageDealt);
	}
	else
	{
		ResultText = FString::Printf(TEXT("Shot %d: MISS"), ShotCount);
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, ResultText);
	
	if (ShotCount >= 10) { GetWorldTimerManager().ClearTimer(ShotTimerHandle); return;}
}

