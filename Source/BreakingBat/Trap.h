// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class BREAKINGBAT_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	TSubclassOf<UDamageType> TrapDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class ABreakingBatCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	FHitResult Hit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float DamageAmount;

	bool bCanApplyDamage;
	FTimerHandle TimerHandle;

public:	

	UFUNCTION(BlueprintCallable, Category = "Trap")
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Trap")
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Trap")
	virtual void ApplyTrapDamage();
};
