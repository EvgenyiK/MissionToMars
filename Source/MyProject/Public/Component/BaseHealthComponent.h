

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UBaseHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBaseHealthComponent();
	float GetHealth()const{return Health;}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
		
};
