// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MountainGameGameMode.h"
#include "MountainCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMountainGameGameMode::AMountainGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/MountainCharacter")); 
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
