#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"



DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ABaseWeapon::StartFire()
{
}

void ABaseWeapon::StopFire()
{
}

void ABaseWeapon::MakeShot()
{
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	CurrentAmmo = DefaultAmmo;
}


APlayerController* ABaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ABaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ABaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility,
	                                     CollisionParams);
}

void ABaseWeapon::DecreaseAmmo()
{
	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		ChangeClip();
	}
}

bool ABaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ABaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void ABaseWeapon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	if (!CurrentAmmo.Infinite)
	{
		CurrentAmmo.Clips--;
	}
	UE_LOG(LogBaseWeapon, Display, TEXT("---Change Clip---"));
}

void ABaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

