
#include "AI/Services/FindEnemyService.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "MUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/MAIPerceptionComponent.h"


UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetOwner();
		const auto PerceptionComponent = MUtils::GetMPlayerComponent<UMAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName,
				PerceptionComponent->GetClosesEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
}
