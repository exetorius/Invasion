// CopyrightNotice


#include "UI/WorkerManagement/HiringScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Core/BaseManagerState.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/RegionalWorkerPool.h"
#include "UI/WorkerManagement/HiringWorkerTileWidget.h"


void UHiringScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InitialiseRegionalPool();	
}

void UHiringScreenWidget::RefreshWorkerList()
{
	PopulateHiringWorkerList();
}

void UHiringScreenWidget::InitialiseRegionalPool()
{
	if (CachedBaseManagerState)
	{
		// Get all the RegionalWorkerPools from the World (there due to AlwaysRelevant)
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegionalWorkerPool::StaticClass(), FoundActors);

		// Iterate over the found actors to find the correct pool for this region
		for (AActor* Pool : FoundActors)
		{
			const ARegionalWorkerPool* CastedPool = Cast<ARegionalWorkerPool>(Pool);
			if (CastedPool && CastedPool->RegionID == CachedBaseManagerState->BaseRegion)
			{
				CachedRegionalPool = Cast<ARegionalWorkerPool>(Pool);
				CachedRegionalPool->OnAvailableWorkersChanged.AddUObject(this, &UHiringScreenWidget::OnRegionalPoolChanged);
				PopulateHiringWorkerList();
				break;
			}
		}
		if (!CachedRegionalPool)
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UHiringScreenWidget::InitialiseRegionalPool);
		}
	}
	else
	{
		InitialiseScreenData();
	}	
}

void UHiringScreenWidget::PopulateHiringWorkerList()
{
	if (!WorkerListScrollBox)
	{
		UE_LOG(LogTemp, Error, TEXT("HiringScreenWidget: WorkerListScrollBox is null - ensure it's bound in Blueprint"));
		return;
	}
	
	if (!CachedBaseManagerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("HiringScreenWidget: No BaseManagerState found for player"));
		return;
	}
	
	if (!CachedRegionalPool)
	{
		UE_LOG(LogTemp, Warning, TEXT("HiringScreenWidget: No RegionalWorkerPool found in level"));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("HiringScreenWidget: Populating worker list"));
	
	WorkerListScrollBox->ClearChildren();	
	
	if (CachedRegionalPool)
	{
		const TArray<UWorkerData*>& AvailableWorkers = CachedRegionalPool->GetAvailableWorkers();
		
		UE_LOG(LogTemp, Log, TEXT("HiringScreenWidget: Populating %d workers"), AvailableWorkers.Num());
		
		for (UWorkerData* Worker : AvailableWorkers)
		{
			if (Worker && WorkerTileClass)
			{
				UE_LOG(LogTemp, Log, TEXT("HiringScreenWidget: WorkerTileClass valid: %s"), WorkerTileClass ? TEXT("YES") : TEXT("NO"));
				if (UHiringWorkerTileWidget* Tile = CreateWidget<UHiringWorkerTileWidget>(this, WorkerTileClass))
				{
					UE_LOG(LogTemp, Log, TEXT("HiringScreenWidget: Processing worker %s"), *Worker->Name);

					Tile->SetWorkerData(Worker);					
					Tile->OnHireClicked.BindUObject(this, &UHiringScreenWidget::OnWorkerHired);
					WorkerListScrollBox->AddChild(Tile);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HiringScreenWidget: Could not get RegionalWorkerPool"));
	}	
}

void UHiringScreenWidget::OnWorkerHired(UWorkerData* Worker)
{
	if (CachedRegionalPool)
	{
		CachedRegionalPool->Server_HireWorker(Worker, CachedBaseManagerState);
	}
}

void UHiringScreenWidget::OnRegionalPoolChanged()
{
	PopulateHiringWorkerList();
}
