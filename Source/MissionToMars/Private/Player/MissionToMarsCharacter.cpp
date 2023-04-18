// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/MissionToMarsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


AMissionToMarsCharacter::AMissionToMarsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
}


void AMissionToMarsCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void AMissionToMarsCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMissionToMarsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMissionToMarsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMissionToMarsCharacter::MoveRight);
}

void AMissionToMarsCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AMissionToMarsCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}



