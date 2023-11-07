
#pragma once

#include "CoreMinimal.h"
#include "UI/MBaseWidget.h"
#include "MyProject/Public/Coretypes.h"
#include "MMenuWidget.generated.h"


class UButton;
class UHorizontalBox;
class UMGameInstance;
class UMLevelItemWidget;
class USoundCue;

UCLASS()
class MYPROJECT_API UMMenuWidget : public UMBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* StartGameSound;
	
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TArray<UMLevelItemWidget*> LevelItemWidgets;
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	UMGameInstance* GetMGameInstance() const;
};
