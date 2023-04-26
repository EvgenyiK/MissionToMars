


#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}


void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


