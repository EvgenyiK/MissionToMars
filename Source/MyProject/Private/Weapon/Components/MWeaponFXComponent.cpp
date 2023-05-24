


#include "Weapon/Components/MWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


UMWeaponFXComponent::UMWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}



void UMWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DefaultEffect, Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());
}



