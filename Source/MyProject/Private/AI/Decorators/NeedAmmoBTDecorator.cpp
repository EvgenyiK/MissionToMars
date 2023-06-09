// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/NeedAmmoBTDecorator.h"
#include "AIController.h"
#include "MUtils.h"
#include "Component/MWeaponComponent.h"


UNeedAmmoBTDecorator::UNeedAmmoBTDecorator()
{
	NodeName = "Need Ammo";
}

bool UNeedAmmoBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = MUtils::GetMPlayerComponent<UMWeaponComponent>(Controller->GetPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
