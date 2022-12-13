// Unreal Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "USCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHOOTER_API UUSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
    float RunModifier = 2.0f;

    virtual float GetMaxSpeed() const override;
};
