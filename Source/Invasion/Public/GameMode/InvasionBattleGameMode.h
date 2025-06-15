// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvasionBattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class INVASION_API AInvasionBattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<class AGridManager> GridManager;
	
};
