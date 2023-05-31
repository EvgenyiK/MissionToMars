
#include "Component/MAIWeaponComponent.h"
#include "Weapon/BaseWeapon.h"

void UMAIWeaponComponent::StartFire()
{
	//if (!CanFire()) return;

	if(CurrentWeapon->IsAmmoEmpty())
	{
		 NextWeapon();
	}else
	{
		CurrentWeapon->StartFire();
	}
	
	Super::StartFire();
}

void UMAIWeaponComponent::NextWeapon()
{
	//if(!CanEquip()) return;
	int32 NextIndex = (CurrentWeaponIndex +1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
	
	
	Super::NextWeapon();
}
