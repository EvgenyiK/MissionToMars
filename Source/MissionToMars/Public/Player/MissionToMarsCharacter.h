// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MissionToMarsCharacter.generated.h"


class UCameraComponent;

UCLASS(Blueprintable)
class AMissionToMarsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMissionToMarsCharacter();

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	virtual void BeginPlay() override;


public:
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

};

