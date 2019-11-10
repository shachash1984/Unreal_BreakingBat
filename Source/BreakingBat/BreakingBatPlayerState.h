// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Components/TimelineComponent.h"
#include "BreakingBatPlayerState.generated.h"

UENUM(BlueprintType)
enum class EDialoguesENUM : uint8
{
	EGameStart UMETA(DisplayName = "QuestStart"),
	EInQuest UMETA(DisplayName = "InQuest"),
	EFinishedQuest UMETA(DisplayName = "QuestEnd"),
	EUnknown UMETA(DisplayName = "None")
};

UCLASS(config = Game)
class BREAKINGBAT_API ABreakingBatPlayerState : public APlayerState
{
	GENERATED_BODY()
		
public:
	ABreakingBatPlayerState();

	UFUNCTION(BlueprintPure, Category = "Score")
	int GetMaxGems();

	UFUNCTION(BlueprintPure, Category="Score")
	int GetGemsCollected();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetGemsCollected(int gemAmount);

	UFUNCTION(BlueprintPure, Category = "Score")
	FText GetGemsIntText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PreviousHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float FullPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PreviousPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float RedFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	class UCurveFloat* PowerCurve;

	UPROPERTY(EditAnywhere, Category = "Power")
	class UMaterialInterface* BatDefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Power")
	class UMaterialInterface* BatNoPowerMaterial;

	FTimeline Timeline;
	float CurveFloatValue;
	float TimelineValue;
	FTimerHandle TimerHandle;
	bool bCanHit;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPower();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float HealthChange);

	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdatePower();

	UFUNCTION(BlueprintPure, Category = "Health")
	FText GetHealthIntText();

	UFUNCTION(BlueprintPure, Category = "Power")
	FText GetPowerIntText();

	UFUNCTION()
	void DamageTimer();

	UFUNCTION()
	void SetDamageState();

	UFUNCTION()
	void SetPowerValue();

	UFUNCTION()
	void SetPowerState();

	UFUNCTION()
	void SetPowerChange(float PowerChange);

	UFUNCTION()
	void HandleOnHit();

	UFUNCTION(BlueprintCallable)
	bool PlayFlash();

	UFUNCTION(BlueprintCallable)
	bool CollectedAllGems();

	void HandleReceivedDamage(float Damage);

	void ReceivePointDamage(float Damage, const UDamageType* DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, AController* InstigatedBy, AActor* DamageCauser, const FHitResult& HitInfo);


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	int32 iGemsCollected;

	int32 iMaxGems;
};
