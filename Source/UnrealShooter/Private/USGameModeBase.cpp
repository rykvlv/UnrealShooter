// Unreal Shooter Game. All Rights Reserved.


#include "USGameModeBase.h"
#include "Player/USBaseCharacter.h"
#include "Player/USPlayerController.h"


AUSGameModeBase::AUSGameModeBase()
{
    DefaultPawnClass = AUSBaseCharacter::StaticClass();
    PlayerControllerClass = AUSPlayerController::StaticClass();
}