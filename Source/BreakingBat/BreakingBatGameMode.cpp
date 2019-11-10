// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BreakingBatGameMode.h"
#include "BreakingBatCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BreakingBatPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "BreakingBatHUD.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

ABreakingBatGameMode::ABreakingBatGameMode() : AGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_BreakingBatCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Setting custom player state
	static ConstructorHelpers::FClassFinder<ABreakingBatPlayerState> PlayerStateBPClass(TEXT("/Game/Blueprints/BP_BrakingBatPlayerState"));
	if (PlayerStateBPClass.Class != NULL)
	{
		PlayerStateClass = PlayerStateBPClass.Class;
		BBPlayerState = Cast<ABreakingBatPlayerState>(PlayerStateClass.GetDefaultObject());
	}
	
	//PlayerStateClass = ABreakingBatPlayerState::StaticClass();

	//Setting custom HUD
	HUDClass = ABreakingBatHUD::StaticClass();
	
}

void ABreakingBatGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlaying);

	BBPlayerState = Cast<ABreakingBatPlayerState>(PlayerStateClass.GetDefaultObject());
}

void ABreakingBatGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetWorld()->GetMapName();

	if (BBPlayerState != nullptr)
	{
		if (FMath::IsNearlyZero(BBPlayerState->GetHealth(), 0.001f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}

EGamePlayState ABreakingBatGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABreakingBatGameMode::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

ABreakingBatCharacter * ABreakingBatGameMode::GetBBPlayerCharacter() const
{
	ABreakingBatCharacter* playerCharacter = Cast<ABreakingBatCharacter>(DefaultPawnClass.GetDefaultObject());
	return playerCharacter;
}

void ABreakingBatGameMode::KillCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetCinematicMode(true, false, false, true, true);
	}
	//ragdoll the character
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (playerCharacter)
	{
		playerCharacter->GetMesh()->SetSimulatePhysics(true);
		playerCharacter->GetMovementComponent()->MovementState.bCanJump = false;
	}
}

void ABreakingBatGameMode::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
		case EGamePlayState::EPlaying:
			break;
		case EGamePlayState::EGameOver:
			break;
		default:
		case EGamePlayState::EUnknown:
			break;
	}
}
