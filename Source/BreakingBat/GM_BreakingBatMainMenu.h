// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_BreakingBatMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGBAT_API AGM_BreakingBatMainMenu : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGM_BreakingBatMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Options")
	float GetMusicVolume();

	UFUNCTION(BlueprintCallable, Category = "Options")
	float GetSoundFXVolume();

	UFUNCTION(BlueprintCallable, Category = "Options")
	void SetMusicVolume(float value);

	UFUNCTION(BlueprintCallable, Category = "Options")
	void SetSoundFXVolume(float value);

	virtual void BeginPlay() override;
private:
	float MusicVolume;
	float SoundFXVolume;
};
