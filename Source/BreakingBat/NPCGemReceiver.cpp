// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCGemReceiver.h"
#include "Components/SphereComponent.h"
#include "BreakingBatCharacter.h"

// Sets default values
ANPCGemReceiver::ANPCGemReceiver()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("NPCInteractionTrigger"));
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetSphereRadius(100.0f);
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPCGemReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCGemReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCGemReceiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCGemReceiver::NotifyActorBeginOverlap(AActor * Other)
{
	ABreakingBatCharacter* player = Cast<ABreakingBatCharacter>(Other);
	if (player)
	{
		player->SetAllowedToInteract(true, this);
	}
	UE_LOG(LogClass, Log, TEXT("ANPCGemReceiver::NotifyActorBeginOverlap"));
}

void ANPCGemReceiver::NotifyActorEndOverlap(AActor * Other)
{
	ABreakingBatCharacter* player = Cast<ABreakingBatCharacter>(Other);
	if (player)
	{
		player->SetAllowedToInteract(false, this);
	}
	UE_LOG(LogClass, Log, TEXT("ANPCGemReceiver::NotifyActorEndOverlap"));
}

