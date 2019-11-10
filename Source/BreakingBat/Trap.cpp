// Fill out your copyright notice in the Description page of Project Settings.

#include "Trap.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "BreakingBatCharacter.h"

// Sets default values
ATrap::ATrap()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	Trigger->InitBoxExtent(FVector(50.0f));
	RootComponent = Trigger;
	

	bCanApplyDamage = false;
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	DamageAmount = 200.0f;
}

void ATrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr))
		return;

	bCanApplyDamage = true;
	PlayerCharacter = Cast<ABreakingBatCharacter>(OtherActor);
	Hit = SweepResult;
	FString DebugString = PlayerCharacter->GetName();
	UE_LOG(LogClass, Log, TEXT("OnOverlapBegin: %s"), *DebugString);
}

void ATrap::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false;
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ATrap::ApplyTrapDamage()
{
	
	if (bCanApplyDamage)
	{
		UGameplayStatics::ApplyPointDamage(PlayerCharacter, DamageAmount, GetActorLocation(), Hit, nullptr, this, TrapDamageType);
		FString DebugString = PlayerCharacter->GetName();
		UE_LOG(LogClass, Log, TEXT("ApplyTrapDamage: %s"), *DebugString);
	}
}

