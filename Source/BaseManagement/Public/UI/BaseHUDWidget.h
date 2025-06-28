// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUDWidget.generated.h"

UENUM()
enum class EBaseOverlay : uint8
{
	EBO_None		UMETA(DisplayName = "None"),
	EBO_Base		UMETA(DisplayName = "Base"),
	EBO_Character	UMETA(DisplayName = "Character"),
	EBO_Inventory	UMETA(DisplayName = "Inventory"),
	EBO_Research	UMETA(DisplayName = "Research"),
	EBO_Engineering UMETA(DisplayName = "Engineering"),

	EBO_DefaultMAX	UMETA(DisplayName="MAX")
};

UCLASS()
class BASEMANAGEMENT_API UBaseHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Switch overlays
	UFUNCTION(BlueprintCallable, Category="BaseHUD")
	void ShowOverlay(EBaseOverlay OverlayType);

protected:
	virtual void NativeConstruct() override;

	void HideAllOverlays() const;

	// Overlay container
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UOverlay> OverlayRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BaseHUD", meta=(BindWidgetOptional));
	TObjectPtr<UUserWidget> BaseViewOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BaseHUD", meta=(BindWidgetOptional));
	TObjectPtr<UUserWidget> CharacterOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BaseHUD", meta=(BindWidgetOptional));
	TObjectPtr<UUserWidget> InventoryOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BaseHUD", meta=(BindWidgetOptional));
	TObjectPtr<UUserWidget> ResearchOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BaseHUD", meta=(BindWidgetOptional));
	TObjectPtr<UUserWidget> EngineeringOverlay;
		
};
