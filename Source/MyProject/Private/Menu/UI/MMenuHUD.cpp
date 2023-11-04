
#include "Menu/UI/MMenuHUD.h"
#include "UI/MBaseWidget.h"


void AMMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UMBaseWidget>(GetWorld(), MenuWidgetClass);
		if(MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}
}
