
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MWeaponFXComponent.generated.h"


class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UMWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UMWeaponFXComponent();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Effect; 
	
public:	

	void PlayImpactFX(const FHitResult& Hit );

		
};
