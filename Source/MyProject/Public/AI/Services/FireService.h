
#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FireService.generated.h"


UCLASS()
class MYPROJECT_API UFireService : public UBTService
{
	GENERATED_BODY()
public:
	UFireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
