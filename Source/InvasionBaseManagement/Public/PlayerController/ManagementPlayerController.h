// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Data/CampaignTypes.h"	
#include "PlayerController/InvasionPlayerController.h"
#include "ManagementPlayerController.generated.h"

/**
 * PlayerController for base management
 * Creates HUD and provides access to the player's BaseManagerState
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API AManagementPlayerController : public AInvasionPlayerController
{
	GENERATED_BODY()

public:
	AManagementPlayerController();
	
	UFUNCTION(Server, Reliable, Category = "UI")
	void Server_RequestSetNation(ENation NewNation);
	
	UFUNCTION(Server, Reliable, Category = "UI")
	void Server_RequestHireWorker(class UWorkerData* Worker, class ARegionalWorkerPool* Pool);
	
	UFUNCTION(Server, Reliable, Category = "UI")
	void Server_RequestFireWorker(UWorkerData* Worker);
	
	UFUNCTION(Server, Reliable, Category = "UI")
	void Server_RequestAssignWorker(UWorkerData* Worker, FGuid TaskID);
	
	UFUNCTION(Server, Reliable, Category = "UI")
	void Server_RequestUnassignWorker(UWorkerData* Worker, FGuid TaskID);
	
protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UManagementHUD> HUDClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UMissionResultScreenWidget> MissionResultScreenClass;

private:
	UPROPERTY()
	TObjectPtr<UManagementHUD> HUD;
	
	UFUNCTION()
	void CreateHUD();
	void CheckPlayerReady();

	// Cached reference to this player's BaseManagerState
	UPROPERTY()
	TObjectPtr<class ABaseManagerState> CachedBaseManagerState;
	
	// Cached reference to the Campaign Game Instance subsystem
	UPROPERTY()
	TObjectPtr<class UInvasionCampaignSubsystem> CachedCampaignSubsystem;
	
// Getters & Setters
public:
	// Get this player's BaseManagerState
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Manager")	
	ABaseManagerState* GetBaseManagerState();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	UManagementHUD* GetManagementHUD() const { return HUD; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subsystem")
	UInvasionCampaignSubsystem* GetCampaignSubsystem();
};
