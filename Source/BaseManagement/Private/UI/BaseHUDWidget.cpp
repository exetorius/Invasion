#include "UI/BaseHUDWidget.h"
#include "Components/Overlay.h"

void UBaseHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Start with base overlay
	ShowOverlay(EBaseOverlay::EBO_Base);
}

void UBaseHUDWidget::ShowOverlay(EBaseOverlay OverlayType)
{
	HideAllOverlays();

	switch (OverlayType)
	{
	case EBaseOverlay::EBO_Base:
		if (BaseViewOverlay) BaseViewOverlay->SetVisibility(ESlateVisibility::Visible);
		break;

	case EBaseOverlay::EBO_Character:
		if (CharacterOverlay) CharacterOverlay->SetVisibility(ESlateVisibility::Visible);
		break;

	case EBaseOverlay::EBO_Inventory:
		if (InventoryOverlay) InventoryOverlay->SetVisibility(ESlateVisibility::Visible);
		break;

	case EBaseOverlay::EBO_Research:
		if (ResearchOverlay) ResearchOverlay->SetVisibility(ESlateVisibility::Visible);
		break;

	case EBaseOverlay::EBO_Engineering:
		if (EngineeringOverlay) EngineeringOverlay->SetVisibility(ESlateVisibility::Visible);
		break;

	default:
		break;
	}
}

void UBaseHUDWidget::HideAllOverlays() const
{
	if (BaseViewOverlay) BaseViewOverlay->SetVisibility(ESlateVisibility::Collapsed);
	if (CharacterOverlay) CharacterOverlay->SetVisibility(ESlateVisibility::Collapsed);
	if (InventoryOverlay) InventoryOverlay->SetVisibility(ESlateVisibility::Collapsed);
	if (ResearchOverlay) ResearchOverlay->SetVisibility(ESlateVisibility::Collapsed);
	if (EngineeringOverlay) EngineeringOverlay->SetVisibility(ESlateVisibility::Collapsed);
}
