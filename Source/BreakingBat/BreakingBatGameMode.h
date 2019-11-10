// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BreakingBatCharacter.h"
#include "BreakingBatGameMode.generated.h"


UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS(minimalapi)
class ABreakingBatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABreakingBatGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	class ABreakingBatPlayerState* BBPlayerState;

	UFUNCTION(BlueprintPure, Category = "GameState")
	EGamePlayState GetCurrentState() const;

	void SetCurrentState(EGamePlayState NewState);

	UFUNCTION(BlueprintPure)
	ABreakingBatCharacter* GetBBPlayerCharacter() const;

	UFUNCTION(BlueprintCallable)
	void KillCharacter();
	

private:

	EGamePlayState CurrentState;

	void HandleNewState(EGamePlayState NewState);
};



