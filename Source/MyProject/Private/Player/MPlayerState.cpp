
#include "Player/MPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogMPlayerState, All, All);

void AMPlayerState::LogInfo()
{
	UE_LOG(LogMPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
