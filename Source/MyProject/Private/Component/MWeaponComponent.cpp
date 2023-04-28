#include "Component/MWeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"


UMWeaponComponent::UMWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}


void UMWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void UMWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->Fire();
	
}