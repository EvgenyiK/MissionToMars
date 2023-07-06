
#include "Menu/UI/MMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMMenuWidget::OnStartGame);
	}
}

void UMMenuWidget::OnStartGame()
{
	const FName StartupLevelName = "MarsMap";
	UGameplayStatics::OpenLevel(this,  StartupLevelName);
}
