#include "UI/ManagementScreens/BaseManagementScreenWidget.h"

void UBaseManagementScreenWidget::NavigationButtonPressed(const EManagementView View) const
{
	OnNavigationButtonPressed.ExecuteIfBound(View);
}
