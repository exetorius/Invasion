// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseManagementScreenWidget.h"
#include "BaseOverviewScreenWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UBaseOverviewScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()
	
protected:
	virtual void OnScreenDataReady() override;	
private:
	void InitialiseOverviewScreen();
	
	void PopulateOverviewScreen();
	void BindChangeDelegates();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WorkerDataText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResearchDataText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> EngineeringDataText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CreditDataText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SuppliesDataText;
};
