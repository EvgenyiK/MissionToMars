

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;


UCLASS()
class MYPROJECT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	virtual void BeginPlay() override;

	

};
