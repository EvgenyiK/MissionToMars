
#include "Menu/MMenuPlayerController.h"
#include "MGameInstance.h"

void AMMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	
}
