#include "Component/BaseHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "MyProject/MyProjectGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UBaseHealthComponent::UBaseHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UBaseHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	SetHealth(Health + HealthAmount);
	return true;
}

bool UBaseHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, 0.0f, MaxHealth);
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
		Killed(InsigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UBaseHealthComponent::HealUpdate,
		                                       HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
}

void UBaseHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UBaseHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UBaseHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UBaseHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld()) return;
	
	const auto GameMode = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if(!GameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}
