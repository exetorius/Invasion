// CopyrightNotice


#include "UI/ManagementScreens/CharacterScreenWidget.h"

void UCharacterScreenWidget::OnBackRequested_Implementation(const EManagementView View) const
{
	OnBackRequested.ExecuteIfBound(View);
}
