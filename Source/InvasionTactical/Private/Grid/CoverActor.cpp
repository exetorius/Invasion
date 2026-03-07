// CopyrightNotice


#include "Grid/CoverActor.h"


ACoverActor::ACoverActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CoverMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoverMesh"));
	SetRootComponent(CoverMeshComponent);
	CoverMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CoverMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CoverMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
}
