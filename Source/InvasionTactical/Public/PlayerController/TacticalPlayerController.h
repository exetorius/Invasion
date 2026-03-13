// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TacticalPlayerController.generated.h"

class ATacticalGridTile;
class UInputAction;
class UInputMappingContext;
class ABaseUnit;
class ATacticalGrid;
class ATurnManager;
/**
 * 
 */
UCLASS()
class INVASIONTACTICAL_API ATacticalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY()
	TObjectPtr<ATacticalGrid> TacticalGrid;
	UPROPERTY()
	TObjectPtr<ATurnManager> TurnManager;
	UPROPERTY()
	TObjectPtr<ABaseUnit> ActiveUnit;
	
	// ENHANCED INPUT
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Tactical;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Select;
	
	UFUNCTION()
	void OnActiveUnitChanged(ABaseUnit* NewActiveUnit);
	
	void OnSelectClicked();
	void RequestMoveToTile(ATacticalGridTile* MoveTile);
};
