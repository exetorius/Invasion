// CopyrightNotice


#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Units/BaseUnit.h"

void UHealthBarWidget::Initialise(ABaseUnit* Unit)
{
	if (!Unit) { return; }
	
	BaseUnit = Unit;
	BaseUnit->OnHealthChanged.AddDynamic(this, &UHealthBarWidget::HandleHealthChanged);	
	HealthProgressBar->SetPercent(BaseUnit->GetHealth() / BaseUnit->GetMaxHealth());
}


void UHealthBarWidget::HandleHealthChanged(const int32 NewHealth)
{
	HealthProgressBar->SetPercent(static_cast<float>(NewHealth) / BaseUnit->GetMaxHealth());
}
