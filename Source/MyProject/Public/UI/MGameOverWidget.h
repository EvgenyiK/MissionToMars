
#pragma once

#include "CoreMinimal.h"
#include "UI/MBaseWidget.h"
#include "MyProject/Public/Coretypes.h"
#include "MGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class MYPROJECT_API UMGameOverWidget : public UMBaseWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(EMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();
};
