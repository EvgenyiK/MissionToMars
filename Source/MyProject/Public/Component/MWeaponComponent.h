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

	void StartFire();
	void StopFire();
	void NextWeapon();

	bool GetWeaponUiData(FWeaponUIData& UIData) const;
	
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponRootAttachPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	//bool EquipAnimInProgress = false;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent,
	const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	//bool CanFire() const;
	//bool CanEquip() const;
};
