// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "MedKitPickup.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGBAT_API AMedKitPickup : public APickup
{
	GENERATED_BODY()
	
public:
	AMedKitPickup();

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	class ABreakingBatCharacter* BBCharacter;
};
