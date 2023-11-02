
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CoreTypes.h"
#include "MGameInstance.generated.h"




UCLASS()
class MYPROJECT_API UMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevelName() const {return StartupLevel;}
	void SetStartupLevelName(const FLevelData& Data) {StartupLevel = Data;}

	TArray<FLevelData>GetLevelsData() const {return LevelsData;}
	
	FName GetMenuLevelName() const {return MenuLevelName;}
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level name must be unique!"))
	TArray<FLevelData>LevelsData;
	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

private:
	FLevelData StartupLevel;
};
