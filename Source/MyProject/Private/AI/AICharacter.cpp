// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/MAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/MAIWeaponComponent.h"
#include "BrainComponent.h"

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
