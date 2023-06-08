
#include "AI/Decorators/HealthPercentBTDecorator.h"
#include "AIController.h"
#include "MUtils.h"
#include "Component/BaseHealthComponent.h"

UHealthPercentBTDecorator::UHealthPercentBTDecorator()
{
	NodeName = "Health Percent";
}

bool UHealthPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = MUtils::GetMPlayerComponent<UBaseHealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
