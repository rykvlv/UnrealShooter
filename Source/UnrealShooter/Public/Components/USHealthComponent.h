// Unreal Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USHealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALSHOOTER_API UUSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUSHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.0f; }

	FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000"))
	float MaxHealth = 100.0f;

private:
    float Health = 0.0f;

	UFUNCTION()
    void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                               AController *InstigateBy, AActor *DamageCauser);
};
