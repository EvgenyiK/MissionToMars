

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MAIController.generated.h"

class UMAIPerceptionComponent;
class URespawnComponent;

UCLASS()
class MYPROJECT_API AMAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMAIController();
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	UMAIPerceptionComponent* MAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	URespawnComponent* RespawnComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};
