#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pathfinder.generated.h"

class AGridManager;

USTRUCT(BlueprintType)
struct FPathNode
{
	GENERATED_BODY()

	FIntPoint GridPosition;
	float GCost;
	float HCost;
	float FCost() const { return GCost + HCost; }
	FPathNode* Parent;
};

UCLASS()
class APathfinder : public AActor
{
	GENERATED_BODY()

public:
	static TArray<FIntPoint> FindPath(const FIntPoint Start, const FIntPoint Goal, const AGridManager* GridManager);

private:
	static float GetHeuristic(FIntPoint A, FIntPoint B);
};
