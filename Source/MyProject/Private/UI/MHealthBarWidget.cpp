
#include "UI/MHealthBarWidget.h"
#include "components/ProgressBar.h"

void UMHealthBarWidget::SetHealthPercent(float Percent)
{
	if(!HealthProgressBar) return;

	const auto HealthBarVisibility = (Percent > PercentColorThreshold || FMath::IsNearlyZero(Percent)
		? ESlateVisibility::Hidden : ESlateVisibility::Visible);

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}
