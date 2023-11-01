
#include "Menu/UI/MMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMMenuWidget, All, All);

void UMMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMMenuWidget::OnStartGame);
	}

	if(QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMMenuWidget::OnQuitGame);
	}
}

void UMMenuWidget::OnStartGame()
{

	if(!GetWorld()) return;

	const auto MGameInstance = GetWorld()->GetGameInstance<UMGameInstance>();
	if(!MGameInstance) return;

	if(MGameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogMMenuWidget, Error, TEXT("Level name is NONE"));
		return;
	}
	
	UGameplayStatics::OpenLevel(this,  MGameInstance->GetStartupLevelName());
}

void UMMenuWidget::OnQuitGame()
{
	if(!GetWorld()) return;

	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(),
		EQuitPreference::Quit, true);

	
	
}
