

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "AICharacter.generated.h"


class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class MYPROJECT_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* UBehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	float HealthVisibilityDistance = 1000.0f;
	
	virtual void BeginPlay() override;
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};
