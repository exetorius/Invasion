// CopyrightNotice


#include "Units/BaseUnit.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameMode/TacticalGameMode.h"
#include "Grid/TacticalGridTile.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HealthBarWidget.h"


ABaseUnit::ABaseUnit()
{
	// TODO: Disable again once billboard of health bar is implemented correctly
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(CapsuleCollider);
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleCollider->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);
	CapsuleCollider->SetCapsuleHalfHeight(88.f);
	CapsuleCollider->SetCapsuleRadius(34.f);
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleCollider);
	MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidgetComponent->SetupAttachment(CapsuleCollider);	
}

void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	// TODO: Move into a UBillboardWidgetComponent subclass so ABaseUnit::Tick can be disabled
	if (HealthBarWidgetComponent)
	{
		if (const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
		{
			const FRotator CameraRot = CameraManager->GetCameraRotation();
			HealthBarWidgetComponent->SetWorldRotation(FRotator(0.f, CameraRot.Yaw + 180.f, 0.f));
		}
	}
}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();	
	
	if (ATacticalGameMode* TacticalGameMode = Cast<ATacticalGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseUnit::BeginPlay — %s calling RegisterUnit"), *GetName());
		TacticalGameMode->RegisterUnit(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ABaseUnit::BeginPlay — %s failed to get ATacticalGameMode"), *GetName());
	}
	
	if (!ensure(HealthBarWidgetComponent)) { return; }
	
	if (UHealthBarWidget* HealthBarWidget = Cast<UHealthBarWidget>(HealthBarWidgetComponent->GetWidget()))
	{
		HealthBarWidget->Initialise(this);
	}	
}

void ABaseUnit::BroadcastOnHealthChanged(const int32 NewHealth)
{
	OnHealthChanged.Broadcast(NewHealth);
}

void ABaseUnit::ConsumeMovementPoints(const int32 Points)
{
	MovementPointsRemaining = FMath::Clamp(MovementPointsRemaining - Points, 0, MovementPointsRemaining);
}

void ABaseUnit::SetFaction(const EFaction NewFaction)
{
	if (Faction == EFaction::None)
	{
		Faction = NewFaction;
	}
	// TODO: Mind control / faction swap mechanic will need to override this blocker
}

void ABaseUnit::ConsumeAttack()
{
	bHasAttackedThisTurn = true;
}

void ABaseUnit::SetCurrentTile(ATacticalGridTile* NewTile)
{
	if (!ensure(NewTile)) { return; }
	
	// Clear the current tile's occupier
	if (CurrentTile && CurrentTile != NewTile)
	{
		CurrentTile->SetOccupyingUnit(nullptr);
	}
	CurrentTile = NewTile;
	NewTile->SetOccupyingUnit(this);
}

void ABaseUnit::Kill()
{
	if (CombatState != ECombatState::Dead)
	{
		if (CurrentTile)
		{
			CurrentTile->SetOccupyingUnit(nullptr);
		}
		Health = 0;
		MovementPointsRemaining = 0;
		CombatState = ECombatState::Dead;
		BroadcastOnHealthChanged(Health);
	}
}

void ABaseUnit::AddHealth(float HealthToAdd)
{
	if (IsAlive())
	{
		Health = FMath::Clamp(Health + HealthToAdd, 0.f, MaxHealth);
		BroadcastOnHealthChanged(Health);
	}
}

void ABaseUnit::RemoveHealth(float HealthToRemove)
{
	if (IsAlive())
	{
		Health = FMath::Max(Health - HealthToRemove, 0.f);
		if (Health <= 0.f)
		{
			Kill();
		}
		BroadcastOnHealthChanged(Health);
	}
}

void ABaseUnit::OnTurnStart()
{
	MovementPointsRemaining = MaxMovementPoints;
	bHasAttackedThisTurn = false;
}


