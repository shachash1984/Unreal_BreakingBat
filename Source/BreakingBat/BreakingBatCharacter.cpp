// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BreakingBatCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Pickup.h"
#include "BreakingBatPlayerState.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"


//////////////////////////////////////////////////////////////////////////
// ABreakingBatCharacter

ABreakingBatCharacter::ABreakingBatCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//Creating pickup trigger
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerTrigger"));
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetSphereRadius(100.0f);

	BatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BatMesh"));
	BatMesh->SetupAttachment(RootComponent);

	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABreakingBatCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABreakingBatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABreakingBatCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABreakingBatCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABreakingBatCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABreakingBatCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABreakingBatCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABreakingBatCharacter::OnResetVR);

	//Bind NPC Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABreakingBatCharacter::DeliverGems);
}

void ABreakingBatCharacter::CollectedGem(int gemValue)
{
	ABreakingBatPlayerState* playerState = GetBBPlayerState();
	if (playerState)
	{
		playerState->SetGemsCollected(playerState->GetGemsCollected() + gemValue);
		/*playerState->GetClass();*/
	}
}

void ABreakingBatCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetBBPlayerState();
	InteractableActor = NULL;
}

void ABreakingBatCharacter::NotifyActorBeginOverlap(AActor * Other)
{
	APickup* pickup = Cast<APickup>(Other);
	if (pickup)
	{
		pickup->OnCollected();
		CollectedGem(pickup->GetScoreValue());
	}
}

ABreakingBatPlayerState* ABreakingBatCharacter::GetBBPlayerState()
{
	if (BBPlayerState == NULL)
	{
		BBPlayerState = GetPlayerState<ABreakingBatPlayerState>();
	}
	return BBPlayerState;
}

bool ABreakingBatCharacter::GetAllowedToInteract()
{
	return bAllowedToInteract;
}

void ABreakingBatCharacter::SetAllowedToInteract(bool allowed, AActor* aInteractableActor)
{
	bAllowedToInteract = allowed;
	if (bAllowedToInteract)
		InteractableActor = aInteractableActor;
	else
		InteractableActor = NULL;
}


void ABreakingBatCharacter::HandleBatMaterialChange(UMaterialInterface * pMat)
{
	BatMesh->SetMaterial(0, pMat);
}

void ABreakingBatCharacter::OnHit_Implementation()
{
	if (!FMath::IsNearlyZero(BBPlayerState->GetPower(), 0.001f) && BBPlayerState->bCanHit)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			//Play swing Bat animation

			//Play swing sound

			BBPlayerState->HandleOnHit();
		}
	}
}

AActor * ABreakingBatCharacter::GetInteractableActor()
{
	return InteractableActor;
}

float ABreakingBatCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogClass, Log, TEXT("ABreakingBatCharacter::TakeDamage"));
	BBPlayerState->HandleReceivedDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABreakingBatCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABreakingBatCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ABreakingBatCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ABreakingBatCharacter::DeliverGems()
{
	if (bAllowedToInteract)
	{
		ABreakingBatPlayerState* playerState = GetBBPlayerState();
		if (playerState)
		{
			playerState->SetGemsCollected(0);
		}
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("Not in interaction range"));
	}
		
}

void ABreakingBatCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABreakingBatCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABreakingBatCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABreakingBatCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
