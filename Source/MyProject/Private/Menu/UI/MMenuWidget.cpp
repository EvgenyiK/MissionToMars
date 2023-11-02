
#include "Menu/UI/MMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/MLevelItemWidget.h"

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

	InitLevelItems();
}

void UMMenuWidget::OnStartGame()
{

	const auto MGameInstance = GetMGameInstance();
	if(!MGameInstance) return;
	
	UGameplayStatics::OpenLevel(this,  MGameInstance->GetStartupLevelName().LevelName);
}

void UMMenuWidget::OnQuitGame()
{
	if(!GetWorld()) return;

	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(),
		EQuitPreference::Quit, true);
	
}

void UMMenuWidget::InitLevelItems()
{
	const auto MGameInstance = GetMGameInstance();
	if(!MGameInstance) return;

	checkf(MGameInstance->GetLevelsData().Num()!=0, TEXT("Levels data must not be empty!"));

	if(!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for (auto LevelData : MGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<UMLevelItemWidget>(GetWorld(),
			LevelItemWidgetClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this,&UMMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (MGameInstance->GetStartupLevelName().LevelName.IsNone())
	{
		OnLevelSelected(MGameInstance->GetLevelsData()[0]);
	}else
	{
		OnLevelSelected(MGameInstance->GetStartupLevelName());
	}
}

void UMMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto MGameInstance = GetMGameInstance();
	if(!MGameInstance) return;

	MGameInstance->SetStartupLevelName(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if(LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

UMGameInstance* UMMenuWidget::GetMGameInstance() const
{
	if(!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UMGameInstance>();
}
