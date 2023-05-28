

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MAIController.generated.h"



UCLASS()
class MYPROJECT_API AMAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
