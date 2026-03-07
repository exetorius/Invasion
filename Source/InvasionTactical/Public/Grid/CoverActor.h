// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TacticalTypes.h"
#include "CoverActor.generated.h"

UCLASS()
class INVASIONTACTICAL_API ACoverActor : public AActor
{
	GENERATED_BODY()

public:
	ACoverActor();
	
	UFUNCTION(BlueprintPure, Category = "Cover")
	ECoverType GetCoverType() const { return CoverType; };
	
private:
	UPROPERTY(EditAnywhere)
	ECoverType CoverType = ECoverType::None;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> CoverMeshComponent;
};
