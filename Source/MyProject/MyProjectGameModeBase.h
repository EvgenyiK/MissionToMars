// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Coretypes.h"
#include "MyProjectGameModeBase.generated.h"


class AAIController;

UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyProjectGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	void SpawnBots();
};
