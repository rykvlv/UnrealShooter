// Unreal Shooter Game. All Rights Reserved.


#include "Player/USBaseCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AUSBaseCharacter::AUSBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent()); 
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

}

