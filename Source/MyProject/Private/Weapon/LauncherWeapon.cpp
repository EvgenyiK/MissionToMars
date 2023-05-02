// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/LauncherWeapon.h"
#include "Weapon/Projectile.h"
#include "Kismet/GameplayStatics.h"

void ALauncherWeapon::StartFire()
{
	MakeShot();
	
}

void ALauncherWeapon::MakeShot()
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(),
		ProjectileClass, SpawnTransform);

	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}


