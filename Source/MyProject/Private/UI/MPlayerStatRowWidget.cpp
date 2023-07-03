
#include "UI/MPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void UMPlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void UMPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}

void UMPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void UMPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if(!PlayerIndicatorImage)return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
