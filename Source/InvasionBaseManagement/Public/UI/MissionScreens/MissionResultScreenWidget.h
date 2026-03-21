// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"
#include "MissionResultScreenWidget.generated.h"

class UMissionBridgeSubsystem;
class UButton;
class UTextBlock;
class UScrollBox;

/**
 * 
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UMissionResultScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CloseWidget();
	
protected:
	virtual void OnScreenDataReady() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CreditsText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> CasualtyListScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ContinueButtonText;
	
	UPROPERTY()
	TObjectPtr<UMissionBridgeSubsystem> MissionBridgeSubsystem;
};
