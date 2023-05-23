#include "Component/MWeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/EquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UMWeaponComponent::UMWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UMWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}


void UMWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
		if (!Weapon) continue;
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}


void UMWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent,
                                             const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UMWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	//EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UMWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UMWeaponComponent::InitAnimations()
{
	if (!EquipAnimMontage) return;
	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<UEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &UMWeaponComponent::OnEquipFinished);
			break;
		}else
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
			checkNoEntry();
		}
	}
}

void UMWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;
	
	//EquipAnimInProgress = false;
}

/*bool UMWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress;
}*/

/*bool UMWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}*/

void UMWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void UMWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UMWeaponComponent::NextWeapon()
{
	//if (!CanEquip())return;
	
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

bool UMWeaponComponent::GetCurrentWeaponUiData(FWeaponUIData& UIData)const
{
	{
		if (CurrentWeapon)
		{
			UIData = CurrentWeapon->GetUIData();
			return true;
		}
		return false;
	};
}

bool UMWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	{
		if (CurrentWeapon)
		{
			AmmoData = CurrentWeapon->GetAmmoData();
			return true;
		}
		return false;
	};
}

bool UMWeaponComponent::TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmount)
{
	
}
