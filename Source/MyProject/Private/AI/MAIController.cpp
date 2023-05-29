


#include "AI/MAIController.h"
#include "AI/AICharacter.h"
#include "Component/MAIPerceptionComponent.h"

AMAIController::AMAIController()
{
	MAIPerceptionComponent = CreateDefaultSubobject<UMAIPerceptionComponent>("MAIPerceptionComponent");
	SetPerceptionComponent(*MAIPerceptionComponent);
}

void AMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto CharacterAI = Cast<AAICharacter>(InPawn);
	if (CharacterAI)
	{
		RunBehaviorTree(CharacterAI->UBehaviorTreeAsset);
	}
}

void AMAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = MAIPerceptionComponent->GetClosesEnemy();
	SetFocus(AimActor);
}
