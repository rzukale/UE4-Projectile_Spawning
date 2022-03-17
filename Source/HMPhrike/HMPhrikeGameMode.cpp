// Copyright Epic Games, Inc. All Rights Reserved.

#include "HMPhrikeGameMode.h"
#include "HMPhrikeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHMPhrikeGameMode::AHMPhrikeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
