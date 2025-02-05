// Copyright Epic Games, Inc. All Rights Reserved.

#include "ValheimGameMode.h"
#include "ValheimCharacter.h"
#include "UObject/ConstructorHelpers.h"

AValheimGameMode::AValheimGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
