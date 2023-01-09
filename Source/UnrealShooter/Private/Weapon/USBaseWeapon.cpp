// Unreal Shooter Game. All Rights Reserved.

#include "Weapon/USBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


AUSBaseWeapon::AUSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMeshComponent); 
}

void AUSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();	
}

