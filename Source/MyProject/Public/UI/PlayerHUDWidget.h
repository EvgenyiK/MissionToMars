// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/Public/Coretypes.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercentt() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUiData(FWeaponUIData& UIData) const;
};
