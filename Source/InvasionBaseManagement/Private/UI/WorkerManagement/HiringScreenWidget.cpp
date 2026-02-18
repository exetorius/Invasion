// CopyrightNotice


#include "UI/WorkerManagement/HiringScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Controller/ManagementPlayerController.h"
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
				if (UHiringWorkerTileWidget* Tile = CreateWidget<UHiringWorkerTileWidget>(this, WorkerTileClass))
				{
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
	if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		if (CachedRegionalPool)
		{
			PC->Server_RequestHireWorker(Worker, CachedRegionalPool);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HiringScreenWidget: Could not get RegionalWorkerPool"));
		}
	}
}

void UHiringScreenWidget::OnRegionalPoolChanged()
{
	PopulateHiringWorkerList();
}
