
#include "Pickups/AmmoPickup.h"
#include "Component/MWeaponComponent.h"
#include "Component/BaseHealthComponent.h"




DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	//подумать над HealthComponent
	const auto HealthComponent = Cast<UBaseHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	//подумать над WeaponComponent
	const auto WeaponComponent = Cast<UMWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
