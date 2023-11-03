

#include "AI/AICharacter.h"
#include "AI/MAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/MAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/MHealthBarWidget.h"
#include "Component/BaseHealthComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit)
	//:Super(ObjInit.SetDefaultSubobjectClass<UMAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AMAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,200.0f, 0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHealthWidgetVisibility();
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthWidgetComponent);
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto MController = Cast<AAIController>(Controller);
	if (MController && MController->BrainComponent)
	{
		MController->BrainComponent->Cleanup();
	}
}

void AAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);
	const auto HealthBarWidget = Cast<UMHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if(!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AAICharacter::UpdateHealthWidgetVisibility()
{
	if(!GetWorld() || !GetWorld()->GetFirstPlayerController() ||
		!GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
	
	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()
	->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
