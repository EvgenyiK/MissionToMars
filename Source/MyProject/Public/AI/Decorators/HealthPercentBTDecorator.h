

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HealthPercentBTDecorator.generated.h"


UCLASS()
class MYPROJECT_API UHealthPercentBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UHealthPercentBTDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
