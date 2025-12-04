// Copyright Epic Games, Inc. All Rights Reserved.

#include "U2_DigilioGameMode.h"
#include "U2_DigilioCharacter.h"
#include "U2_DigilioPlayerController.h"
#include "U2_Digilio/Scripts/U2_PlayerState.h"
#include "U2_Digilio/Scripts/U2_DigilioHUD.h"
#include "U2_Digilio/Scripts/U2_DigilioGameState.h"


AU2_DigilioGameMode::AU2_DigilioGameMode()
{
	DefaultPawnClass = AU2_DigilioCharacter::StaticClass();
	
	PlayerControllerClass = AU2_DigilioPlayerController::StaticClass();
	
	PlayerStateClass = AU2_PlayerState::StaticClass();

	GameStateClass = AU2_DigilioGameState::StaticClass();
	
	HUDClass = AU2_DigilioHUD::StaticClass();
}
