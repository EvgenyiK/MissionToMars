
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MMenuPlayerController.generated.h"



UCLASS()
class MYPROJECT_API AMMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
