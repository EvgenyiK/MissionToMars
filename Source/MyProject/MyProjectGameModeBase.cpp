// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/GameHUD.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}
