// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/MissionToMarsCharacter.h"
#include "Camera/CameraComponent.h"


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
}


