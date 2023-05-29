

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MAIController.generated.h"

class UMAIPerceptionComponent;

UCLASS()
class MYPROJECT_API AMAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMAIController();
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	UMAIPerceptionComponent* MAIPerceptionComponent;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
};
