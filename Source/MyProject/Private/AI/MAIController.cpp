


#include "AI/MAIController.h"
#include "AI/AICharacter.h"
#include "Component/MAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AMAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
