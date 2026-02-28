// CopyrightNotice


#include "GameMode/ManagementGameMode.h"
#include "Controller/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "Systems/RegionalWorkerPool.h"
#include "GameFramework/PlayerState.h"

AManagementGameMode::AManagementGameMode()
{
	bUseSeamlessTravel = true;
	PlayerControllerClass = AManagementPlayerController::StaticClass(); // Can be overriden in the BP if required

	// Set default classes
	BaseManagerStateClass = ABaseManagerState::StaticClass();
	RegionalWorkerPoolClass = ARegionalWorkerPool::StaticClass();

	// Default regions
	RegionNames.Add(FName("Europe"));
	RegionNames.Add(FName("North America"));
	RegionNames.Add(FName("Asia"));
	RegionNames.Add(FName("Oceania"));

	DefaultPlayerRegion = FName("Europe");
}

void AManagementGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn regional worker pools on server
	if (HasAuthority())
	{
		SpawnRegionalWorkerPools();
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
		NewBaseState->SetBaseRegion(DefaultPlayerRegion); // Assign default region
		PlayerBaseStates.Add(NewPlayer->PlayerState, NewBaseState);

		UE_LOG(LogTemp, Log, TEXT("ManagementGameMode: Created BaseManagerState for player %s in region %s"),
			*NewPlayer->PlayerState->GetPlayerName(),
			*DefaultPlayerRegion.ToString());
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
	for (const FName& RegionName : RegionNames)
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
