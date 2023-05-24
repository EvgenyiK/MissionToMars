
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MWeaponFXComponent.generated.h"


class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UMWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UMWeaponFXComponent();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* DefaultEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
	
public:	

	void PlayImpactFX(const FHitResult& Hit );

		
};
