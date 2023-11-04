// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyProject/Public/Coretypes.h"
#include "GameHUD.generated.h"


class UMBaseWidget;

UCLASS()
class MYPROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
	virtual void BeginPlay()override;
	
private:
	UPROPERTY()
	TMap<EMatchState, UMBaseWidget*> GameWidgets; 

	UPROPERTY()
	UMBaseWidget* CurrentWidget = nullptr;
	
	void DrawCrossHair();
	void OnMatchStateChanged(EMatchState State);
};
