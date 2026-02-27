// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseManagementScreenWidget.h"
#include "Data/CampaignTypes.h"
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
	
	// TODO: Move these to a separate class when we flesh out the start game menus
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UComboBoxString> PlayerNationComboBox;
	UFUNCTION()
	void OnNationSelected(FString SelectedItem, ESelectInfo::Type SelectionType);
	void PopulateNationComboBox();
	ENation StringToNation(FString String);
	FString NationToString(ENation Nation);
	
	// TODO END
};
