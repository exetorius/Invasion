// CopyrightNotice

#include "UI/ManagementNavigationWidget.h"

void UManagementNavigationWidget::NavigationButtonPressed(const EManagementView View) const
{
	OnNavigationButtonPressed.ExecuteIfBound(View);
}
