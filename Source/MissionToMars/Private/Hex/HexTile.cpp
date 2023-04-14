// Fill out your copyright notice in the Description page of Project Settings.


#include "Hex/HexTile.h"


// Sets default values
AHexTile::AHexTile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(RootComponent);
}


