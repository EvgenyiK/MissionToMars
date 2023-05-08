// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if(PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void AGameHUD::DrawCrossHair()
{

	const TInterval<float>Center(Canvas->SizeX * 0.5f,Canvas->SizeY * 0.5f);
	
	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Center.Min - HalfLineSize,Center.Max, Center.Min + HalfLineSize, Center.Max,
		LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize,
		LineColor, LineThickness);
}
