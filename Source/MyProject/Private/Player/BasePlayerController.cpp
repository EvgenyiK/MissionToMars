
#include "Player/BasePlayerController.h"
#include "Component/RespawnComponent.h"

ABasePlayerController::ABasePlayerController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}
