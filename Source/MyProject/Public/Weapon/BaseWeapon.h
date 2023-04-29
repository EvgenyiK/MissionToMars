

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;


UCLASS()
class MYPROJECT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "Muzzle_01";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 01.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;


	
	virtual void BeginPlay() override;

	void MakeShot();
	
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd)const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	void MakeDamage(FHitResult& HitResult);

private:
	FTimerHandle ShotTimerHandle;
};
