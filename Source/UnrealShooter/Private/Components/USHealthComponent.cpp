// Unreal Shooter Game. All Rights Reserved.


#include "Components/USHealthComponent.h"

// Sets default values for this component's properties
UUSHealthComponent::UUSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UUSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}