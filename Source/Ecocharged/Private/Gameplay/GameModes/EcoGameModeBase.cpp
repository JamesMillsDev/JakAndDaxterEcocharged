// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameModes/EcoGameModeBase.h"

#include "Actors/Player/EcoCharacter.h"
#include "Actors/Player/EcoHUD.h"
#include "Actors/Player/EcoPlayerController.h"
#include "Actors/Player/EcoPlayerState.h"

AEcoGameModeBase::AEcoGameModeBase()
{
	DefaultPawnClass = AEcoCharacter::StaticClass();
	HUDClass = AEcoHUD::StaticClass();
	PlayerControllerClass = AEcoPlayerController::StaticClass();
	PlayerStateClass = AEcoPlayerState::StaticClass();
}
