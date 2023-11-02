

#include "Menu/UI/MGoToMenuWidget.h"
#include "Components/Button.h"
#include "MGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGoToMenuWidget, All, All);

void UMGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UMGoToMenuWidget::OnGoToMenu);
	}
}

void UMGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto MGameInstance = GetWorld()->GetGameInstance<UMGameInstance>();
	if(!MGameInstance) return;

	if(MGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogMGoToMenuWidget, Error, TEXT("Menu Level name is NONE"));
		return;
	}
	
	UGameplayStatics::OpenLevel(this,  MGameInstance->GetMenuLevelName());
}
