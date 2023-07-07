
#include "Menu/MMenuPlayerController.h"
#include "MGameInstance.h"

void AMMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	GetWorld()->GetGameInstance<UMGameInstance>()->TestString = "Menu level says hello";
}
