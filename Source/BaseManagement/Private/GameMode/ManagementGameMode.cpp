// CopyrightNotice


#include "GameMode/ManagementGameMode.h"
#include "Controller/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "GameFramework/PlayerState.h"

AManagementGameMode::AManagementGameMode()
{
	bUseSeamlessTravel = true;
	PlayerControllerClass = AManagementPlayerController::StaticClass(); // Can be overriden in the BP if required

	// Set default BaseManagerState class
	BaseManagerStateClass = ABaseManagerState::StaticClass();
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
		NewBaseState->OwningPlayerState = NewPlayer->PlayerState;
		PlayerBaseStates.Add(NewPlayer->PlayerState, NewBaseState);

		UE_LOG(LogTemp, Log, TEXT("ManagementGameMode: Created BaseManagerState for player %s"),
			*NewPlayer->PlayerState->GetPlayerName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ManagementGameMode: Failed to spawn BaseManagerState for player %s"),
			*NewPlayer->PlayerState->GetPlayerName());
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
