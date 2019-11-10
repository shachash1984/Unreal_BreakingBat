// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "FireTrap.generated.h"


/**
 * 
 */
UCLASS()
class BREAKINGBAT_API AFireTrap : public ATrap
{
	GENERATED_BODY()

public:
	AFireTrap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UParticleSystemComponent* Fire;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void ApplyTrapDamage() override;

protected:
	virtual void BeginPlay() override;
};
