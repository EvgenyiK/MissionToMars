
#include "Component/MAIPerceptionComponent.h"
#include "AIController.h"
#include "MUtils.h"
#include "Component/BaseHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UMAIPerceptionComponent::GetClosesEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = MUtils::GetMPlayerComponent<UBaseHealthComponent>(PercieveActor);
		if (HealthComponent && !HealthComponent->IsDead()) //TODO: check if enemies or not
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}
