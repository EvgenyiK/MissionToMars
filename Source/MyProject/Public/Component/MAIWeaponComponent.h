
#pragma once

#include "CoreMinimal.h"
#include "Component/MWeaponComponent.h"
#include "MAIWeaponComponent.generated.h"




UCLASS()
class MYPROJECT_API UMAIWeaponComponent : public UMWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
