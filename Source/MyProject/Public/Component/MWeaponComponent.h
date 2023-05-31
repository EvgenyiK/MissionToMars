#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyProject/Public/Coretypes.h"
#include "Weapon/BaseWeapon.h"
#include "MWeaponComponent.generated.h"

class ABaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UMWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();

	bool GetCurrentWeaponUiData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	auto TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmount) -> bool;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponRootAttachPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//bool CanFire() const;
	//bool CanEquip() const;

	void EquipWeapon(int32 WeaponIndex);
	

private:
	
	//bool EquipAnimInProgress = false;

	void SpawnWeapons();
	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent,
	                          const FName& SocketName);
	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
};
