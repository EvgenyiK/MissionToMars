
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MGameInstance.generated.h"




UCLASS()
class MYPROJECT_API UMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FString TestString = "Hello game!";
	
};
