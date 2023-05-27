// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "Component/BaseHealthComponent.h"
#include "Component/MWeaponComponent.h"


float UPlayerHUDWidget::GetHealthPercentt() const
{
	const auto HealthComponent = GetHealthComponent();
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::GetCurrentWeaponUiData(FWeaponUIData& UIData) const
{
	
	const auto WeaponComponent = GetWeaponComponent();
	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUiData(UIData);
}

bool UPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	
	const auto WeaponComponent = GetWeaponComponent();
	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UPlayerHUDWidget::Initialize()
{
	const auto HealthComponent = GetHealthComponent();
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUDWidget::OnHealthChanged);
	}
	
	return Super::Initialize();
}

UMWeaponComponent* UPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr ;

	const auto Component = Player->GetComponentByClass(UMWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UMWeaponComponent>(Component);
	return WeaponComponent;
}

UBaseHealthComponent* UPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr ;

	const auto Component = Player->GetComponentByClass(UBaseHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UBaseHealthComponent>(Component);
	return HealthComponent;
}

void UPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
	
}

