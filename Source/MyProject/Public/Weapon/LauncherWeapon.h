


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class AProjectile;
class USoundCue;

/**
 * 
 */
UCLASS()
class MYPROJECT_API ALauncherWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* NoAmmoSound;
	
	virtual void MakeShot() override;
};
