// Unreal Shooter Game. All Rights Reserved.


#include "Components/USHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
UUSHealthComponent::UUSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

	AActor *ComponentOwner = GetOwner();
	if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UUSHealthComponent::OnTakeAnyDamage);
    }
}

void UUSHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                             AController *InstigateBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || IsDead()) return;

    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}