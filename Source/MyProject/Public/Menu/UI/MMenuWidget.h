
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/Public/Coretypes.h"
#include "MMenuWidget.generated.h"


class UButton;
class UHorizontalBox;
class UMGameInstance;
class UMLevelItemWidget;

UCLASS()
class MYPROJECT_API UMMenuWidget : public UUserWidget
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
