// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

#include "AIController.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/GameHUD.h"


DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);


AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}

void AMyProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	SpawnBots();

	CurrentRound = 1;
	StartRound();
}

UClass* AMyProjectGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMyProjectGameModeBase::SpawnBots()
{
	if(!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto MAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(MAIController);
	}
}

void AMyProjectGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AMyProjectGameModeBase::GameTimerUpdate,
		1.0f, true);
}

void AMyProjectGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogGameModeBase, Display, TEXT("Time: %i / Round: %i/%i "), RoundCountDown, CurrentRound, GameData.RoundsNum);
	
	if(--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		if(CurrentRound + 1 <= GameData.RoundsNum )
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogGameModeBase, Display, TEXT("---GAME OWER---"))
		}
	}
}

void AMyProjectGameModeBase::ResetPlayers()
{
	if(!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AMyProjectGameModeBase::ResetOnePlayer(AController* Controller)
{
	if(Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
		
	RestartPlayer(Controller);
}
