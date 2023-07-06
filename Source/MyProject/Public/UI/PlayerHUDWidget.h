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

	//не вызывается в блюпринт
	UFUNCTION(BlueprintImplementableEvent, Category = "Ui")
	void OnTakeDamage();

	
protected:	
	virtual void NativeOnInitialized() override;
	
private:
	UMWeaponComponent* GetWeaponComponent() const;
	UBaseHealthComponent* GetHealthComponent() const;
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
};
