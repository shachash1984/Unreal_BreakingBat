// Fill out your copyright notice in the Description page of Project Settings.

#include "FireTrap.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"

AFireTrap::AFireTrap() : ATrap()
{
	Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particles"));
	Fire->SetRelativeLocation(FVector::ZeroVector);
	Fire->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFireTrap::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AFireTrap::OnOverlapEnd);
}

void AFireTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATrap::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if ((OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr))
		return;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFireTrap::ApplyTrapDamage, 2.2f, true, 0.0f);
}

void AFireTrap::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ATrap::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void AFireTrap::ApplyTrapDamage()
{
	ATrap::ApplyTrapDamage();
}

void AFireTrap::BeginPlay()
{
	Super::BeginPlay();
}
