

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;


UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;
	
	virtual void BeginPlay() override;



};
