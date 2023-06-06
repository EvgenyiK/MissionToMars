
#include "AI/Services/ChangeWeaponService.h"
#include "Component/MWeaponComponent.h"
#include "AIController.h"
#include "MUtils.h"

UChangeWeaponService::UChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = MUtils::GetMPlayerComponent<UMWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}


