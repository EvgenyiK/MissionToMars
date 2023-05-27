// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

class UMWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class MYPROJECT_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ARifleWeapon();
	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 01.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UMWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd)const override;
	
private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	
	void MakeDamage(FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visible);
};
