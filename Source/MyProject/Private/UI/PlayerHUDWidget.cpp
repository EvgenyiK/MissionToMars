// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "Component/BaseHealthComponent.h"
#include "Component/MWeaponComponent.h"

float UPlayerHUDWidget::GetHealthPercentt() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f ;

	const auto Component = Player->GetComponentByClass(UBaseHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UBaseHealthComponent>(Component);
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::GetWeaponUiData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return false ;

	const auto Component = Player->GetComponentByClass(UMWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UMWeaponComponent>(Component);
	if(!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUiData(UIData);
}
