


#include "Component/BaseHealthComponent.h"


UBaseHealthComponent::UBaseHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}



void UBaseHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UBaseHealthComponent::OnTakeAnyDamage);
	}
}

void UBaseHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType,
			class AController* InsigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}




