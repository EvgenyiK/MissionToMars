
#include "Pickups/HealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"))	
	return true;
}
