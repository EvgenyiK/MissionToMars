// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UMPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UMPauseWidget::OnClearPause);
	}
}

void UMPauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GetWorld()->GetAuthGameMode()->ClearPause();
}
