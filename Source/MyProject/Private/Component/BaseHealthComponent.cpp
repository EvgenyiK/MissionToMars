


#include "Component/BaseHealthComponent.h"
#include "Math/UnrealMathUtility.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UBaseHealthComponent::UBaseHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}



void UBaseHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UBaseHealthComponent::OnTakeAnyDamage);
	}
}

void UBaseHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType,
			class AController* InsigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	
}




