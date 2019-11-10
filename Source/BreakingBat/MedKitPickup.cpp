// Fill out your copyright notice in the Description page of Project Settings.

#include "MedKitPickup.h"
#include "BreakingBatCharacter.h"
#include "BreakingBatPlayerState.h"

AMedKitPickup::AMedKitPickup()
{
	OnActorBeginOverlap.AddDynamic(this, &AMedKitPickup::OnOverlap);
}

void AMedKitPickup::OnOverlap(AActor * MyOverlappedActor, AActor * OtherActor)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		BBCharacter = Cast<ABreakingBatCharacter>(OtherActor);
		ABreakingBatPlayerState* state = Cast<ABreakingBatPlayerState>(BBCharacter->GetPlayerState());
		if (BBCharacter && state && state->GetHealth() < 1.0f)
		{
			state->UpdateHealth(100.0f);
			Destroy();
		}
	}
}
