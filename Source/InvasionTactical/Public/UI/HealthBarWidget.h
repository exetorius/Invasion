// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class ABaseUnit;
/**
 * 
 */
UCLASS()
class INVASIONTACTICAL_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:		
	void Initialise(ABaseUnit* Unit);
	
private:
	UFUNCTION()
	void HandleHealthChanged(const int32 NewHealth);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;
	
	UPROPERTY()
	TObjectPtr<ABaseUnit> BaseUnit;
	
	// Getters & setter
public:
	UFUNCTION(BlueprintPure)
	ABaseUnit* GetBaseUnit() const { return BaseUnit; }
};
