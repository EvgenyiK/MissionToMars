


#include "Weapon/Components/MWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"


UMWeaponFXComponent::UMWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}



void UMWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());
}



