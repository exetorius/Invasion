// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathfinderTest.generated.h"

UCLASS()
class INVASIONTACTICAL_API APathfinderTest : public AActor
{
	GENERATED_BODY()

public:
	APathfinderTest();

	UPROPERTY(EditAnywhere)
	FIntPoint DefenderCoords;
	UPROPERTY(EditAnywhere)
	FIntPoint AttackerCoords;
protected:
	virtual void BeginPlay() override;

};
