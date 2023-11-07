

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MBaseWidget.generated.h"

class USoundCue;

UCLASS()
class MYPROJECT_API UMBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();
	
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* OpenSound;
};
