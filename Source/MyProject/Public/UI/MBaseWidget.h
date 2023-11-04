

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MBaseWidget.generated.h"


UCLASS()
class MYPROJECT_API UMBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();
	
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;
};
