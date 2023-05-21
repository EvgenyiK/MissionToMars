
#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

}


void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"))
	Destroy();
}


void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

