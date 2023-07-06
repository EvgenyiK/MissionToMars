// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPauseWidget.generated.h"

class UButton;

UCLASS()
class MYPROJECT_API UMPauseWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnClearPause();
};
