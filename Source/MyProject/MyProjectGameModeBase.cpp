// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

#include "AIController.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/GameHUD.h"
#include "Player/MPlayerState.h"


DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);


AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AMPlayerState::StaticClass();
}

void AMyProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	SpawnBots();
	CreateTeamsInfo();
	CurrentRound = 1;
	StartRound();
}

UClass* AMyProjectGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMyProjectGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AMPlayerState>(KillerController->PlayerState)
	: nullptr;

	const auto VictimPlayerState = VictimController ? Cast<AMPlayerState>(VictimController->PlayerState)
	: nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
}

void AMyProjectGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

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
	UE_LOG(LogGameModeBase, Display, TEXT("Time: %i / Round: %i/%i "), RoundCountDown, CurrentRound,
	       GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogGameModeBase, Display, TEXT("---GAME OWER---"))
			LogPlayerInfo();
		}
	}
}

void AMyProjectGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AMyProjectGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AMyProjectGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AMPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		
		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AMyProjectGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if(TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}

	UE_LOG(LogGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"),
		TeamID, *GameData.DefaultTeamColor.ToString());

	return GameData.DefaultTeamColor;
}

void AMyProjectGameModeBase::SetPlayerColor(AController* Controller)
{
	if(!Controller) return;
	const auto Character = Cast<ABaseCharacter>(Controller->GetPawn());
	if(!Character) return;

	const auto PlayerState = Cast<AMPlayerState>(Controller->PlayerState);
	if(!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AMyProjectGameModeBase::LogPlayerInfo()
{

	if(!GetWorld()) return;
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AMPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}
