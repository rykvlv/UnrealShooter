// Unreal Shooter Game. All Rights Reserved.


#include "Components/USHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
UUSHealthComponent::UUSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSHealthComponent::BeginPlay()
{
	Super::BeginPlay();


    SetHealth(MaxHealth);

	AActor *ComponentOwner = GetOwner();
	if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UUSHealthComponent::OnTakeAnyDamage);
    }
}

void UUSHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                             AController *InstigateBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (EnableAutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UUSHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void UUSHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UUSHealthComponent::SetHealth(float NewHealth) 
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
