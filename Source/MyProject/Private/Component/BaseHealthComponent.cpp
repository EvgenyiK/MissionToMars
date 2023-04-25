


#include "Component/BaseHealthComponent.h"
#include "Dev/FireDamageType.h"
#include "Dev/IceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

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
	UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);

	if(DamageType)
	{
		if(DamageType->IsA<UFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("So hooot"));
		}else if (DamageType->IsA<UIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("coold"));
		}
	}
}




