#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pathfinder.generated.h"

class AGridManager;

USTRUCT(BlueprintType)
struct FPathNode
{
	GENERATED_BODY()

	FIntVector GridPosition;
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
	TArray<FIntVector> FindPath(const FIntVector Start, const FIntVector Goal, const AGridManager* GridManager);

private:
	static float GetHeuristic(FIntVector A, FIntVector B);
};
