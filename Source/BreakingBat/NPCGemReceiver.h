// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCGemReceiver.generated.h"

UCLASS()
class BREAKINGBAT_API ANPCGemReceiver : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCGemReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*trigger for player interaction*/
	UPROPERTY(EditAnywhere)
	class USphereComponent* Trigger;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* Other) override;

	virtual void NotifyActorEndOverlap(AActor* Other) override;

};
