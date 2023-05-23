
#include "Pickups/HealthPickup.h"
#include "Component/BaseHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	//подумать над HealthComponent
	const auto HealthComponent = Cast<UBaseHealthComponent>(PlayerPawn);
	if(!HealthComponent) return false ;
	return HealthComponent->TryToAddHealth(HealthAmount);
}
