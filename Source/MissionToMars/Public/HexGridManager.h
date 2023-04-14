// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridManager.generated.h"

class AHexTile;

UCLASS()
class MISSIONTOMARS_API AHexGridManager : public AActor
{
	GENERATED_BODY()

protected:
	TArray<TArray<AHexTile*>> HexGrid2DArray;

	UPROPERTY(EditAnyWhere, Category = "HexGrid|Layout")
	int32 GridWidth;

	UPROPERTY(EditAnyWhere, Category = "HexGrid|Layout")
	int32 GridHeight;


	UPROPERTY(EditAnyWhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> GrassHexTile;

	UPROPERTY(EditAnyWhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> WaterHexTile;

	UPROPERTY(EditAnyWhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> SandHexTile;

	UPROPERTY(EditAnyWhere, Category = "HexGrid|Setup")
	float ChanceOfWater;

public:	
	// Sets default values for this actor's properties
	AHexGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float TileHorizontalOffset = 700;
	float OddRowHorizontalOffset = 350;
	float TileVerticalOffset = 600;


};
