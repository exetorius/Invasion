// CopyrightNotice


#include "Grid/TacticalGridTile.h"

#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"
#include "Grid/CoverActor.h"


ATacticalGridTile::ATacticalGridTile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	HighlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighlightMesh"));
	SetRootComponent(HighlightMesh);
	HighlightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HighlightMesh->SetVisibility(false);
	
	ClickCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickCollision"));
	ClickCollision->SetupAttachment(GetRootComponent());
	// TODO: Drive from BoxHalfExtents — currently hardcoded to match default. Will drift if BoxHalfExtents is changed in BP.
	ClickCollision->SetBoxExtent(FVector(50.f)); 
	ClickCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ClickCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ClickCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Block);
}

void ATacticalGridTile::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Move to a helper function to unbloat BeginPlay
	if (const UWorld* World = GetWorld())
	{
		const bool bBlocked = World->OverlapAnyTestByChannel(
			GetActorLocation(),
			FQuat::Identity,
			ECC_GameTraceChannel1,
			FCollisionShape::MakeBox(FVector(BoxHalfExtents)),
			FCollisionQueryParams::DefaultQueryParam
			);
		bIsWalkable = !bBlocked;
		
		// TODO: The below functions need moving into a helper function
		// North
		TArray<FOverlapResult> OverlapResult;
		World->OverlapMultiByChannel(
			OverlapResult,
			GetActorLocation() + FVector(BoxHalfExtents, 0.f, 0.f),
			FQuat::Identity,
			ECC_GameTraceChannel2,
			FCollisionShape::MakeBox(FVector(10.f, BoxHalfExtents/2.f, BoxHalfExtents)),
			FCollisionQueryParams::DefaultQueryParam
			);
		for (FOverlapResult& Overlap : OverlapResult)
		{
			if (ACoverActor* CoverActor = Cast<ACoverActor>(Overlap.GetActor()))
			{
				CoverData.North = CoverActor->GetCoverType();
				UE_LOG(LogTemp, Warning, TEXT("ATacticalGridTile::BeginPlay - North CoverType detected: %s"), *UEnum::GetValueAsString(CoverActor->GetCoverType()));
				break;
			}
		}
		
		// East
		OverlapResult.Reset();		
		World->OverlapMultiByChannel(
			OverlapResult,
			GetActorLocation() + FVector(0.f, BoxHalfExtents, 0.f),
			FQuat::Identity,
			ECC_GameTraceChannel2,
			FCollisionShape::MakeBox(FVector(BoxHalfExtents/2.f, 10.f, BoxHalfExtents)),
			FCollisionQueryParams::DefaultQueryParam
			);
		for (FOverlapResult& Overlap : OverlapResult)
		{
			if (ACoverActor* CoverActor = Cast<ACoverActor>(Overlap.GetActor()))
			{
				CoverData.East = CoverActor->GetCoverType();
				UE_LOG(LogTemp, Warning, TEXT("ATacticalGridTile::BeginPlay - East CoverType detected: %s"), *UEnum::GetValueAsString(CoverActor->GetCoverType()));
				break;
			}
		}
		
		//South
		OverlapResult.Reset();
		World->OverlapMultiByChannel(
			OverlapResult,
			GetActorLocation() + FVector(-BoxHalfExtents, 0.f, 0.f),
			FQuat::Identity,
			ECC_GameTraceChannel2,
			FCollisionShape::MakeBox(FVector(10.f, BoxHalfExtents/2.f, BoxHalfExtents)),
			FCollisionQueryParams::DefaultQueryParam
			);
		for (FOverlapResult& Overlap : OverlapResult)
		{
			if (ACoverActor* CoverActor = Cast<ACoverActor>(Overlap.GetActor()))
			{
				CoverData.South = CoverActor->GetCoverType();
				UE_LOG(LogTemp, Warning, TEXT("ATacticalGridTile::BeginPlay - South CoverType detected: %s"), *UEnum::GetValueAsString(CoverActor->GetCoverType()));
				break;
			}
		}
		
		// West
		OverlapResult.Reset();		
		World->OverlapMultiByChannel(
			OverlapResult,
			GetActorLocation() + FVector(0.f, -BoxHalfExtents, 0.f),
			FQuat::Identity,
			ECC_GameTraceChannel2,
			FCollisionShape::MakeBox(FVector(BoxHalfExtents/2.f, 10.f, BoxHalfExtents)),
			FCollisionQueryParams::DefaultQueryParam
			);
		for (FOverlapResult& Overlap : OverlapResult)
		{
			if (ACoverActor* CoverActor = Cast<ACoverActor>(Overlap.GetActor()))
			{
				CoverData.West = CoverActor->GetCoverType();
				UE_LOG(LogTemp, Warning, TEXT("ATacticalGridTile::BeginPlay - West CoverType detected: %s"), *UEnum::GetValueAsString(CoverActor->GetCoverType()));
				break;
			}
		}
	}
		
	HighlightMaterial = UMaterialInstanceDynamic::Create(HighlightMesh->GetMaterial(0), this);
	if (!ensure(HighlightMaterial)) { return; }
	HighlightMesh->SetMaterial(0, HighlightMaterial);
}

void ATacticalGridTile::SetHighlighted(bool bHighlighted)
{	
	if (!ensure(HighlightMaterial)) { return; }
	
	HighlightMaterial->SetScalarParameterValue("Highlighted", bHighlighted ? 1.f : 0.f);
	HighlightMesh->SetVisibility(bHighlighted);	
	bIsHighlighted = bHighlighted;
}

