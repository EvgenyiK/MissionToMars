// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionToMarsGameMode.h"
#include "Player/MissionToMarsPlayerController.h"
#include "Player/MissionToMarsCharacter.h"


AMissionToMarsGameMode::AMissionToMarsGameMode()
{
	DefaultPawnClass = AMissionToMarsGameMode::StaticClass();
	PlayerControllerClass = AMissionToMarsPlayerController::StaticClass();
	
}