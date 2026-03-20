// CopyrightNotice


#include "GameMode/ManagementGameMode.h"
#include "PlayerController/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "Systems/RegionalWorkerPool.h"
#include "GameFramework/PlayerState.h"
#include "Data/CampaignTypes.h"
#include "Data/MissionData.h"
#include "Subsystems/MissionBridgeSubsystem.h"

AManagementGameMode::AManagementGameMode()
{
	bUseSeamlessTravel = true;
	PlayerControllerClass = AManagementPlayerController::StaticClass(); // Can be overriden in the BP if required

	// Set default classes
	BaseManagerStateClass = ABaseManagerState::StaticClass();
	RegionalWorkerPoolClass = ARegionalWorkerPool::StaticClass();
}

void AManagementGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn regional worker pools on server
	if (HasAuthority())
	{
		SpawnRegionalWorkerPools();
		if (UMissionBridgeSubsystem* MissionBridgeSubsystem = GetGameInstance()->GetSubsystem<UMissionBridgeSubsystem>())
		{
			FMissionResult MissionResult = MissionBridgeSubsystem->GetPendingMissionResult();
			if (MissionResult.CasualtyIDs.Num() == 0 && MissionResult.CreditsAwarded == 0)
			{
				MissionBridgeSubsystem->ClearPendingMissionResult();
				return;
			}
			if (PlayerBaseStates.Num() > 0)
			{
				ABaseManagerState* BaseManagerState = PlayerBaseStates.CreateIterator().Value();
				for (FGuid CasualtyID : MissionResult.CasualtyIDs)
				{
					if (UWorkerData* Soldier = BaseManagerState->FindWorkerByGUID(CasualtyID))
					{
						UE_LOG(LogTemp, Log, TEXT("ManagementGameMode: Removing casualty — %s"), *Soldier->GetWorkerName());
						BaseManagerState->RemoveWorker(Soldier);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("ManagementGameMode: Casualty GUID not found in roster — %s"), *CasualtyID.ToString());
					}
				}
				BaseManagerState->AddCredits(MissionResult.CreditsAwarded);
				UE_LOG(LogTemp, Log, TEXT("ManagementGameMode: Credits awarded — %d | Total credits — %d"),
					MissionResult.CreditsAwarded, BaseManagerState->GetCredits());
			}
			MissionBridgeSubsystem->ClearPendingMissionResult();
		}
	}
}

void AManagementGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Create a BaseManagerState for this player
	CreateBaseManagerStateForPlayer(NewPlayer);
}

void AManagementGameMode::CreateBaseManagerStateForPlayer(APlayerController* NewPlayer)
{
	if (!NewPlayer || !NewPlayer->PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("ManagementGameMode: Cannot create BaseManagerState - invalid player"));
		return;
	}

	// Check if this player already has a base state
	if (PlayerBaseStates.Contains(NewPlayer->PlayerState))
	{
		UE_LOG(LogTemp, Warning, TEXT("ManagementGameMode: Player %s already has a BaseManagerState"),
			*NewPlayer->PlayerState->GetPlayerName());
		return;
	}

	// Spawn the BaseManagerState actor
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = NewPlayer;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABaseManagerState* NewBaseState = GetWorld()->SpawnActor<ABaseManagerState>(
		BaseManagerStateClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (NewBaseState)
	{
		NewBaseState->SetOwningPlayerState(NewPlayer->PlayerState);
		const TArray<FName>& Regions = GetAllUniqueRegions(); // TODO: Assign once player has picked starting region #24 issue
		NewBaseState->SetBaseRegion(Regions[0]); 
		PlayerBaseStates.Add(NewPlayer->PlayerState, NewBaseState);

		UE_LOG(LogTemp, Log, TEXT("ManagementGameMode: Created BaseManagerState for player %s in region %s"),
			*NewPlayer->PlayerState->GetPlayerName(),
			*Regions[0].ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ManagementGameMode: Failed to spawn BaseManagerState for player %s"),
			*NewPlayer->PlayerState->GetPlayerName());
	}
}

void AManagementGameMode::SpawnRegionalWorkerPools()
{
	if (!RegionalWorkerPoolClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ManagementGameMode: RegionalWorkerPoolClass is not set!"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn a pool for each region
	for (const FName& RegionName : GetAllUniqueRegions())
	{
		ARegionalWorkerPool* Pool = GetWorld()->SpawnActor<ARegionalWorkerPool>(
			RegionalWorkerPoolClass,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParams
		);

		if (Pool)
		{
			Pool->SetRegionID(RegionName);
			RegionalWorkerPools.Add(RegionName, Pool);

			// Generate initial workers (5 of each type for testing)
			Pool->GenerateInitialWorkerPool(5, 5, 5, 5, 5);

			UE_LOG(LogTemp, Log, TEXT("ManagementGameMode: Spawned RegionalWorkerPool for region: %s"), *RegionName.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ManagementGameMode: Failed to spawn RegionalWorkerPool for region: %s"), *RegionName.ToString());
		}
	}
}

ABaseManagerState* AManagementGameMode::GetBaseManagerStateForPlayer(APlayerState* PlayerState) const
{
	if (const TObjectPtr<ABaseManagerState>* FoundState = PlayerBaseStates.Find(PlayerState))
	{
		return *FoundState;
	}

	return nullptr;
}

ARegionalWorkerPool* AManagementGameMode::GetRegionalPool(FName RegionID) const
{
	if (const TObjectPtr<ARegionalWorkerPool>* FoundPool = RegionalWorkerPools.Find(RegionID))
	{
		return *FoundPool;
	}

	return nullptr;
}
