// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/Public/Coretypes.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */

class UBaseHealthComponent;
class UMWeaponComponent;

UCLASS()
class MYPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercentt() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUiData(FWeaponUIData& UIData) const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;
	
private:
	UMWeaponComponent* GetWeaponComponent() const;
	UBaseHealthComponent* GetHealthComponent() const;
};
