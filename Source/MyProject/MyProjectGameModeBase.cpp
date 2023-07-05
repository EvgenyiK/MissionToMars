// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

#include "AIController.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/GameHUD.h"
#include "Player/MPlayerState.h"
#include "MUtils.h"
#include "Component/RespawnComponent.h"
#include "EngineUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

constexpr static int32 MinRoundTimeForeRespawn = 10;

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

	SetMatchState(EMatchState::InProgress);
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

	StartRespawn(VictimController);
}

void AMyProjectGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool AMyProjectGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

	if(PauseSet)
	{
		SetMatchState(EMatchState::Pause);
	}
	
	return PauseSet;
}

bool AMyProjectGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if(PauseCleared)
	{
		SetMatchState(EMatchState::InProgress);
	}

	return PauseCleared;
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
			GameOver();
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
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player":"Bot");
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

void AMyProjectGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailable = RoundCountDown > MinRoundTimeForeRespawn + GameData.RespawnTime;
	if(!RespawnAvailable)return;
	
	const auto RespawnComponent = MUtils::GetMPlayerComponent<URespawnComponent>(Controller);
	if(!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void AMyProjectGameModeBase::GameOver()
{
	UE_LOG(LogGameModeBase, Display, TEXT("---GAME OWER---"))
	LogPlayerInfo();

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if(Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(EMatchState::GameOver);
}

void AMyProjectGameModeBase::SetMatchState(EMatchState State)
{
	if(MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}
