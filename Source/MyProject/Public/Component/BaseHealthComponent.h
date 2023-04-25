

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UBaseHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBaseHealthComponent();
	float GetHealth()const{return Health;}

	UFUNCTION(BlueprintCallable)
	bool IsDead() const{return Health <= 0.0;}

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType,
			class AController* InsigatedBy, AActor* DamageCauser);	
};
