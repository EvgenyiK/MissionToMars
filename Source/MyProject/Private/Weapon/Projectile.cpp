


#include "Weapon/Projectile.h"
#include "Components/SphereComponent.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



