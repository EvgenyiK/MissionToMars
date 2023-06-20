
#include "UI/SpectatorWidget.h"
#include "MUtils.h"
#include "Component/RespawnComponent.h"

bool USpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = MUtils::GetMPlayerComponent<URespawnComponent>(GetOwningPlayer());
	if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
