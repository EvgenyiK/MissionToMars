#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MWeaponComponent.generated.h"

class ABaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UMWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMWeaponComponent();

	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();
};
