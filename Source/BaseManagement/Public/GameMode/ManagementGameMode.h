// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ManagementGameMode.generated.h"

class ABaseManagerState;
/**
 * GameMode for base management screen
 * Spawns a BaseManagerState for each player that joins
 */
UCLASS()
class BASEMANAGEMENT_API AManagementGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AManagementGameMode();

	// Called when a player logs in - creates their BaseManagerState
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Get the BaseManagerState for a specific player
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	ABaseManagerState* GetBaseManagerStateForPlayer(APlayerState* PlayerState) const;

protected:
	// Class to spawn for each player's base state
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base Manager")
	TSubclassOf<ABaseManagerState> BaseManagerStateClass;

private:
	// Map of PlayerState to their BaseManagerState
	UPROPERTY()
	TMap<TObjectPtr<APlayerState>, TObjectPtr<class ABaseManagerState>> PlayerBaseStates;

	void CreateBaseManagerStateForPlayer(APlayerController* NewPlayer);
};
