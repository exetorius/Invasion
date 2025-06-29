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
	FVector Location = FVector(0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBlocked = false;
};

UCLASS()
class INVASION_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 GridWidth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 GridHeight = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 GridDepth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 CellSize = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 CellHeight = 200.f;

private:
	TArray<FGridCell> GridCells;
	
// Getters & Setters
public:
	FORCEINLINE int32 GetGridWidth() const { return GridWidth; } 
	FORCEINLINE int32 GetGridHeight() const { return GridHeight; }
	FVector GetCellWorldLocation(int32 X, int32 Y, int32 Z) const;
	FIntVector GetClosestGridIndex(const FVector& WorldLocation) const;
};
