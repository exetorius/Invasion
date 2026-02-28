// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorkerTileBase.generated.h"

class UWorkerData;
class UButton;
class UTextBlock;

/**
 * Abstract base class for all worker tiles.
 * Handles data storage, action button wiring, and label configuration.
 * Blueprint subclasses define role-specific stat display via OnWorkerDataSet.
 */
UCLASS(Abstract)
class INVASIONBASEMANAGEMENT_API UWorkerTileBase : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnActionClicked, UWorkerData*);
	FOnActionClicked OnActionClicked;

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SetWorkerData(UWorkerData* Worker);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tile")
	UWorkerData* GetWorkerData() const { return WorkerData; }

	// Sets the action button label — call this after creating the tile (e.g. "Hire", "Fire", "Assign")
	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SetActionLabel(const FText& Label);

protected:
	virtual void NativeConstruct() override;

	// Implement in Blueprint to update role-specific stat display when worker data is set
	UFUNCTION(BlueprintImplementableEvent, Category = "Tile")
	void OnWorkerDataSet(UWorkerData* Worker);

private:
	UFUNCTION()
	void OnActionButtonClicked();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "Tile")
	TObjectPtr<UButton> ActionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "Tile")
	TObjectPtr<UTextBlock> ActionLabelText;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Tile")
	TObjectPtr<UWorkerData> WorkerData;
};
