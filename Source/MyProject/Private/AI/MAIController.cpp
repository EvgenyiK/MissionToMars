


#include "AI/MAIController.h"
#include "AI/AICharacter.h"

void AMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto CharacterAI = Cast<AAICharacter>(InPawn);
	if (CharacterAI)
	{
		RunBehaviorTree(CharacterAI->UBehaviorTreeAsset);
	}
}
