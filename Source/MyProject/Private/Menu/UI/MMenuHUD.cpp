
#include "Menu/UI/MMenuHUD.h"
#include "Blueprint/UserWidget.h"


void AMMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if(MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}
