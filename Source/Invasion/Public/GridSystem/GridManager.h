// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBlocked;
};

UCLASS()
class INVASION_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridWidth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridHeight = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CellSize = 100.f;

private:
	TArray<FGridCell> GridCells;
	
// Getters & Setters
public:
};
