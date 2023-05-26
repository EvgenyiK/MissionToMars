
#include "Component/BaseHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UBaseHealthComponent::UBaseHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}

bool UBaseHealthComponent::TryToAddHealth(float HealthAmount)
{
	if(IsDead() || IsHealthFull()) return false;
	SetHealth(Health + HealthAmount);
	return true;
}

bool UBaseHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health,0.0f,MaxHealth);
}


void UBaseHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth >0);
	SetHealth(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UBaseHealthComponent::OnTakeAnyDamage);
	}
}

void UBaseHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType,
			class AController* InsigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	SetHealth(Health - Damage);
	
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if (IsDead())
	{
		OnDeath.Broadcast();
	}else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UBaseHealthComponent::HealUpdate,
			HealUpdateTime,true, HealDelay);
	}

	PlayCamerashake();
}

void UBaseHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	OnHealthChanged.Broadcast(Health);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UBaseHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void UBaseHealthComponent::PlayCamerashake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}





