// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/LauncherWeapon.h"
#include "Weapon/Projectile.h"


void ALauncherWeapon::StartFire()
{
	MakeShot();
}

void ALauncherWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(
		ProjectileClass, SpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
	SpawnMuzzleFX();
}
