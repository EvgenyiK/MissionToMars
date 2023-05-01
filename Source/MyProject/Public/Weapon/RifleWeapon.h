// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 01.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;
	
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd)const override;
	
private:
	FTimerHandle ShotTimerHandle;
};
