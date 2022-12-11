// Unreal Shooter Game. All Rights Reserved.


#include "Player/USBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AUSBaseCharacter::AUSBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AUSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AUSBaseCharacter::MoveForward(float Amount)
{
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
