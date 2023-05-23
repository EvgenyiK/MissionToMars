// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

class ABaseWeapon;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ABaseWeapon> WeaponType;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn)override;	
};
