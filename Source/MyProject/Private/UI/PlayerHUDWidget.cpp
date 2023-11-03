
#include "UI/PlayerHUDWidget.h"

#include "MUtils.h"
#include "Component/BaseHealthComponent.h"
#include "Component/MWeaponComponent.h"
#include "Components/ProgressBar.h"
#include "Player/MPlayerState.h"


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

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
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

	UpdateHealthBar();
}

void UPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = MUtils::GetMPlayerComponent<UBaseHealthComponent>(NewPawn);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUDWidget::OnHealthChanged);
	}

	UpdateHealthBar();
}

int32 UPlayerHUDWidget::GetKillsNum() const
{
	const auto Controller = GetOwningPlayer();
	if(!Controller) return 0;

	const auto PlayerState = Cast<AMPlayerState>(Controller->PlayerState);
	return PlayerState ? PlayerState->GetKillsNum(): 0;
}

FString UPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32  MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if (SymbolsNumToAdd >0 )
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}

void UPlayerHUDWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercentt() > PercentColorThreshold ?
			GoodColor:BadColor);
	}
}

