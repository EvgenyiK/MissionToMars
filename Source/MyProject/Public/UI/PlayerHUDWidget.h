// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Public/Coretypes.h"
#include "UI/MBaseWidget.h"
#include "PlayerHUDWidget.generated.h"



class UBaseHealthComponent;
class UMWeaponComponent;
class UProgressBar;


UCLASS()
class MYPROJECT_API UPlayerHUDWidget : public UMBaseWidget
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

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString FormatBullets(int32 BulletsNum) const;
	
protected:
	UPROPERTY(meta = (Bindwidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DamageAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;
	
	virtual void NativeOnInitialized() override;
	
private:
	UMWeaponComponent* GetWeaponComponent() const;
	UBaseHealthComponent* GetHealthComponent() const;
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
	void UpdateHealthBar();
};
