
#include "Player/BasePlayerController.h"
#include "Component/RespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ABasePlayerController::ABasePlayerController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this,  &ABasePlayerController::OnPauseGame);
}

void ABasePlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}
