
#include "Pickups/AmmoPickup.h"
#include "Component/MWeaponComponent.h"
#include "Component/BaseHealthComponent.h"




DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto Component = PlayerPawn->GetComponentByClass(UMWeaponComponent::StaticClass());

	const auto HealthComponent = Cast<UBaseHealthComponent>(Component);
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	
	const auto WeaponComponent = Cast<UMWeaponComponent>(Component);
	if (!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
