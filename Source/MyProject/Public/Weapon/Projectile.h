

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UMWeaponFXComponent;


UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectile();

	void SetShotDirection(const FVector& Direction){ShotDirection = Direction;}

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float LifeSeconds = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UMWeaponFXComponent* WeaponFXComponent;
	
	virtual void BeginPlay() override;

private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit );

	AController* GetController() const;
};
