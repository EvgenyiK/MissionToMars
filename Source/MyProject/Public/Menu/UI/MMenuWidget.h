
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MMenuWidget.generated.h"


class UButton;

UCLASS()
class MYPROJECT_API UMMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;
	
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();
};
