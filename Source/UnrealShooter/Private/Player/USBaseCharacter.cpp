// Unreal Shooter Game. All Rights Reserved.


#include "Player/USBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/USCharacterMovementComponent.h"
#include "Components/USHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
AUSBaseCharacter::AUSBaseCharacter(const FObjectInitializer &ObjInit) 
    : 
    Super(ObjInit.SetDefaultSubobjectClass<UUSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UUSHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AUSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AUSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AUSBaseCharacter::OnHealthChanged);
}

// Called every frame
void AUSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUSBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUSBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AUSBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &AUSBaseCharacter::TurnAround);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AUSBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AUSBaseCharacter::OnStopRunning);
}

void AUSBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f ? true : false;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AUSBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void AUSBaseCharacter::LookUp(float Amount)
{
    AddControllerPitchInput(Amount);
}

void AUSBaseCharacter::TurnAround(float Amount)
{
    AddControllerYawInput(Amount);
}

void AUSBaseCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void AUSBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}

bool AUSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AUSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

    return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AUSBaseCharacter::OnDeath()
{
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);
}

void AUSBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}