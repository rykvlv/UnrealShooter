// Unreal Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class UNREALSHOOTER_API AUSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AUSBaseWeapon();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMeshComponent;

	virtual void BeginPlay() override;

};
