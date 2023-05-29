

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MAIPerceptionComponent.generated.h"


UCLASS()
class MYPROJECT_API UMAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosesEnemy() const;
};
