

#include "Menu/UI/MLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UMLevelItemWidget::OnLevelItemClicked);
		LevelSelectButton->OnHovered.AddDynamic(this, &UMLevelItemWidget::OnLevelItemHovered);
		LevelSelectButton->OnUnhovered.AddDynamic(this, &UMLevelItemWidget::OnLevelItemUnovered);
	}
}

void UMLevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}

void UMLevelItemWidget::OnLevelItemHovered()
{
	if(FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMLevelItemWidget::OnLevelItemUnovered()
{
	if(FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UMLevelItemWidget::SetSelected(bool IsSelected)
{
	if (LevelImage)
	{
		LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
	}
}

void UMLevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName)); 
	}

	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

