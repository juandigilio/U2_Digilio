// Copyright Epic Games, Inc. All Rights Reserved.

#include "U2_DigilioGameMode.h"
#include "U2_DigilioCharacter.h"
#include "U2_DigilioPlayerController.h"
#include "U2_Digilio/Scripts/U2_PlayerState.h"
/*#include "U2_GameState.h"
#include "U2_HUD.h"*/


AU2_DigilioGameMode::AU2_DigilioGameMode()
{
	DefaultPawnClass = AU2_DigilioCharacter::StaticClass();

	/*// Controller del jugador
	PlayerControllerClass = playercon::StaticClass();

	// PlayerState propio
	PlayerStateClass = AU2_PlayerState::StaticClass();

	// GameState (si lo tenés)
	GameStateClass = AU2_GameState::StaticClass();

	// HUD propio
	HUDClass = AU2_HUD::StaticClass();*/
}
