// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HiringWorkerTileWidget.generated.h"

class UWorkerData;
/**
 *  Widget representing a single working in the hiring list
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UHiringWorkerTileWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	DECLARE_DELEGATE_OneParam(FOnHireClicked, UWorkerData*);
	FOnHireClicked OnHireClicked;
	
	UFUNCTION(BlueprintCallable, Category = "Hiring")
	void OnHireButtonClicked();
	
	// Set the worker data and update UI
	UFUNCTION(BlueprintCallable, Category = "Hiring")
	void SetWorkerData(UWorkerData* Worker);
	
	// Get the current worker data
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Hiring")
	UWorkerData* GetWorkerData() const { return WorkerData; }

protected:
	// Called after SetWorkerData to update UI elements
	// Implement this in Blueprint to bind text blocks, images, etc.
	UFUNCTION(BlueprintImplementableEvent, Category = "Hiring")
	void OnWorkerDataSet(UWorkerData* Worker);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Hiring")
	TObjectPtr<UWorkerData> WorkerData;
};
