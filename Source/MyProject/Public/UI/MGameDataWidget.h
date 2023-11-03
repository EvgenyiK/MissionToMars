#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGameDataWidget.generated.h"

class AGameModeBase;
class APlayerState;

UCLASS()
class MYPROJECT_API UMGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	AGameModeBase* GetGameMode() const;
	APlayerState* GetPlayerState() const;
};
