#include "UI/MGameDataWidget.h"
#include "MyProject/MyProjectGameModeBase.h"
#include "Player/MPlayerState.h"

int32 UMGameDataWidget::GetKillsNum() const
{
	const auto PlayerS = GetPlayerState();
	const auto PlayerState = Cast<AMPlayerState>(PlayerS);
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UMGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMod = GetGameMode();
	const auto GameMode = Cast<AMyProjectGameModeBase>(GameMod);
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UMGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMod = GetGameMode();
	const auto GameMode = Cast<AMyProjectGameModeBase>(GameMod);
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UMGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMod = GetGameMode();
	const auto GameMode = Cast<AMyProjectGameModeBase>(GameMod);
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

AGameModeBase* UMGameDataWidget::GetGameMode() const
{
	return GetWorld() ? Cast<AGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

APlayerState* UMGameDataWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? Cast<AMPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
