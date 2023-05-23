
#include "Pickups/AmmoPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	return true;
}
