// CopyrightNotice


#include "UI/ManagementScreens/WorldScreenWidget.h"

void UWorldScreenWidget::OnWorldButtonClicked_Implemented(const EManagementView View) const
{
	OnWorldButtonClicked.ExecuteIfBound(View);
}
