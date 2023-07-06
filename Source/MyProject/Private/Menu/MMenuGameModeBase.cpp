
#include "Menu/MMenuGameModeBase.h"
#include "Menu/MMenuPlayerController.h"
#include "Menu/UI/MMenuHUD.h"

AMMenuGameModeBase::AMMenuGameModeBase()
{
	PlayerControllerClass = AMMenuPlayerController::StaticClass();
	HUDClass = AMMenuHUD::StaticClass();
}
