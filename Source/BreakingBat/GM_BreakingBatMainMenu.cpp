// Fill out your copyright notice in the Description page of Project Settings.

#include "GM_BreakingBatMainMenu.h"
#include "BreakingBatCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BreakingBatPlayerState.h"

AGM_BreakingBatMainMenu::AGM_BreakingBatMainMenu()
{
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

	//Setting DefaultPawnClass
	DefaultPawnClass = ABreakingBatCharacter::StaticClass();
	//Setting custom player state
	PlayerStateClass = ABreakingBatPlayerState::StaticClass();
	
}

float AGM_BreakingBatMainMenu::GetMusicVolume()
{
	return MusicVolume;
}

float AGM_BreakingBatMainMenu::GetSoundFXVolume()
{
	return SoundFXVolume;
}

void AGM_BreakingBatMainMenu::SetMusicVolume(float value)
{
	MusicVolume = value;
}

void AGM_BreakingBatMainMenu::SetSoundFXVolume(float value)
{
	SoundFXVolume = value;
}

void AGM_BreakingBatMainMenu::BeginPlay()
{
	Super::BeginPlay();
}
