// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BreakingBatCharacter.generated.h"

UCLASS(config=Game)
class ABreakingBatCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	

public:
	ABreakingBatCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable)
	void HandleBatMaterialChange(UMaterialInterface* pMat);

	UFUNCTION(BlueprintNativeEvent, Category = "Hit")
	void OnHit();
	void OnHit_Implementation();

	UFUNCTION(BlueprintCallable)
	AActor* GetInteractableActor();

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return BatMesh; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/* Deliver all collected gems to NPC*/
	void DeliverGems();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void CollectedGem(int gemValue);

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BatMesh;

	//current Actor to interact with
	AActor* InteractableActor;

private:
	//Pickup collection trigger
	UPROPERTY()
	class USphereComponent* Trigger;

	//NPC interaction flag
	bool bAllowedToInteract;

	

	UPROPERTY()
	class ABreakingBatPlayerState* BBPlayerState;

	UFUNCTION(BlueprintCallable)
	ABreakingBatPlayerState* GetBBPlayerState();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void NotifyActorBeginOverlap(AActor* Other) override;

	/*Getter for bAllowedToInteract*/
	UFUNCTION(BlueprintCallable, Category = "NPC Interaction")
	bool GetAllowedToInteract();

	/*Setter for bAllowedToInteract*/
	UFUNCTION(BlueprintCallable, Category = "NPC Interaction")
	void SetAllowedToInteract(bool allowed, AActor* aInteractableActor);

	
	
};

