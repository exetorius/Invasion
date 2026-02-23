// CopyrightNotice


#include "Controller/ManagementPlayerController.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "CheatManager/InvasionCheatManager.h"
#include "UI/ManagementHUD.h"
#include "Core/BaseManagerState.h"
#include "GameMode/ManagementGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/RegionalWorkerPool.h"

AManagementPlayerController::AManagementPlayerController()
{
	CheatClass = UInvasionCheatManager::StaticClass();
}

void AManagementPlayerController::Server_RequestHireWorker_Implementation(UWorkerData* Worker,
	ARegionalWorkerPool* Pool)
{
	if (!Worker || !Pool) { return;}
	
	if (ABaseManagerState* Base = GetBaseManagerState())
	{
		// Already server-authoritative, call implementation directly
		Pool->Server_HireWorker_Implementation(Worker, Base);
	}	
}

void AManagementPlayerController::Server_RequestFireWorker_Implementation(UWorkerData* Worker)
{
	if (!Worker) { return;}
	
	if (ABaseManagerState* Base = GetBaseManagerState())
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegionalWorkerPool::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			if (ARegionalWorkerPool* Pool = Cast<ARegionalWorkerPool>(Actor))
			{
				if (Pool->GetRegionID() == Base->GetBaseRegion())
				{
					// Already server-authoritative, call implementation directly
					Pool->Server_ReturnWorker_Implementation(Worker);
					Base->RemoveWorker(Worker);					
					break;
				}
			}
		}		
	}
}

void AManagementPlayerController::Server_RequestAssignWorker_Implementation(UWorkerData* Worker, FGuid TaskID)
{
	if (!Worker || !TaskID.IsValid()) { return;}
	
	if (ABaseManagerState* Base = GetBaseManagerState())
	{
		Base->AssignWorkerToTask(Worker, TaskID);
	}
}

void AManagementPlayerController::Server_RequestUnassignWorker_Implementation(UWorkerData* Worker, FGuid TaskID)
{
	if (!Worker || !TaskID.IsValid()) { return;}
	
	if (ABaseManagerState* Base = GetBaseManagerState())
	{
		Base->UnassignWorkerFromTask(Worker, TaskID);
	}
}

void AManagementPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CheckPlayerReady();
}

void AManagementPlayerController::CheckPlayerReady()
{
	if (GetBaseManagerState())
	{
		CreateHUD();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AManagementPlayerController::CheckPlayerReady);
	}
}

void AManagementPlayerController::CreateHUD()
{
	if (IsLocalPlayerController())
	{
		if (HUDClass)
		{
			HUD = CreateWidget<UManagementHUD>(this, HUDClass);
			if (HUD)
			{
				HUD->AddToViewport();

				const FInputModeUIOnly InputMode;
				SetInputMode(InputMode);
				bShowMouseCursor = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ManagementPlayerController: HUDClass is not set!"));
		}
	}
}

ABaseManagerState* AManagementPlayerController::GetBaseManagerState() const
{
	// Return cached if available
	if (CachedBaseManagerState)
	{
		return CachedBaseManagerState;
	}

	if (!PlayerState)
	{
		return nullptr;
	}

	// Server: Use GameMode lookup (faster)
	if (HasAuthority())
	{
		if (const AManagementGameMode* GameMode = Cast<AManagementGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			CachedBaseManagerState = GameMode->GetBaseManagerStateForPlayer(PlayerState);
			return CachedBaseManagerState;
		}
	}
	// Client: Search through replicated BaseManagerState actors
	else
	{
		for (TActorIterator<ABaseManagerState> It(GetWorld()); It; ++It)
		{
			ABaseManagerState* State = *It;
			if (State && State->GetOwningPlayerState() == PlayerState)
			{
				CachedBaseManagerState = State;
				UE_LOG(LogTemp, Log, TEXT("ManagementPlayerController: Client found BaseManagerState via TActorIterator"));
				return CachedBaseManagerState;
			}
		}
	}

	return nullptr;
}
