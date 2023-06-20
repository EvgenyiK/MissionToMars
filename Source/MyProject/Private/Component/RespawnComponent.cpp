#include "Component/RespawnComponent.h"
#include "MyProject/MyProjectGameModeBase.h"


URespawnComponent::URespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &URespawnComponent::RespawnTimerUpdate, 1.0,
	                                       true);
}

bool URespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void URespawnComponent::RespawnTimerUpdate()
{
	if(--RespawnCountDown == 0)
	{
		if(!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if(!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
