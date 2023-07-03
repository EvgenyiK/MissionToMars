
#include "UI/MGameOverWidget.h"
#include "MyProject/MyProjectGameModeBase.h"
#include "Player/MPlayerState.h"
#include "UI/MPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "MUtils.h"

bool UMGameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UMGameOverWidget::OnMatchStateChanged);
		}
	}
	return Super::Initialize();
}

void UMGameOverWidget::OnMatchStateChanged(EMatchState State)
{
	if(State == EMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void UMGameOverWidget::UpdatePlayersStat()
{
	if(!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<AMPlayerState>(Controller->PlayerState);
		if(!PlayerState)continue;

		const auto PlayerStateRowWidget = CreateWidget<UMPlayerStatRowWidget>(GetWorld(),
			PlayerStatRowWidgetClass);
		if(!PlayerStateRowWidget) continue;

		PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStateRowWidget->SetKills(MUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStateRowWidget->SetDeaths(MUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStateRowWidget->SetTeam(MUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStateRowWidget);
	}
}
