// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ManagementPlayerController.generated.h"

class ABaseManagerState;

/**
 * PlayerController for base management
 * Creates HUD and provides access to player's BaseManagerState
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API AManagementPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AManagementPlayerController();
	
	UFUNCTION(Server, Reliable, Category = "UI")
	void Server_RequestHireWorker(class UWorkerData* Worker, class ARegionalWorkerPool* Pool);
	
protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UManagementHUD> HUDClass;

private:
	UPROPERTY()
	TObjectPtr<UManagementHUD> HUD;
	
	UFUNCTION()
	void CreateHUD();
	void CheckPlayerReady();

	// Cached reference to this player's BaseManagerState
	UPROPERTY()
	mutable TObjectPtr<ABaseManagerState> CachedBaseManagerState;
	
// Getters & Setters
public:
	// Get this player's BaseManagerState
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Manager")	
	ABaseManagerState* GetBaseManagerState() const;
};
