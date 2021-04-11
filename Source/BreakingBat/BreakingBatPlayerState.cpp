// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakingBatPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Curves/CurveFloat.h"
#include "BreakingBatCharacter.h"

ABreakingBatPlayerState::ABreakingBatPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

int ABreakingBatPlayerState::GetMaxGems()
{
	return iMaxGems;
}

int ABreakingBatPlayerState::GetGemsCollected()
{
	return iGemsCollected;
}

void ABreakingBatPlayerState::SetGemsCollected(int gemAmount)
{
	iGemsCollected = gemAmount;
	UE_LOG(LogClass, Log, TEXT("PlayerState updated: %d"), iGemsCollected);
}

FText ABreakingBatPlayerState::GetGemsIntText()
{
	FString MaxGemsString = FString::FromInt(iMaxGems);
	FString GemsCollectedString = FString::FromInt(iGemsCollected);
	FString GemsHUD = GemsCollectedString + FString(TEXT("/")) + MaxGemsString;
	FText GemsText = FText::FromString(GemsHUD);
	return GemsText;
}

bool ABreakingBatPlayerState::PlayFlash()
{
	if (RedFlash)
	{
		RedFlash = false;
		return true;
	}
	return false;
	UE_LOG(LogClass, Log, TEXT("PlayFlash"));
}

bool ABreakingBatPlayerState::CollectedAllGems()
{
	return iGemsCollected >= iMaxGems;
}

void ABreakingBatPlayerState::HandleReceivedDamage(float Damage)
{
	SetCanBeDamaged(false);
	RedFlash = true;
	UpdateHealth(-Damage);
	DamageTimer();
}

void ABreakingBatPlayerState::ReceivePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo)
{
	/*bCanBeDamaged = false;
	RedFlash = true;
	UpdateHealth(-Damage);
	DamageTimer();*/
}

void ABreakingBatPlayerState::BeginPlay()
{
	Super::BeginPlay();

	FullHealth = 1000.0f;
	Health = FullHealth;
	HealthPercentage = Health / FullHealth;
	PreviousHealth = HealthPercentage;
	SetCanBeDamaged(true);
	iMaxGems = 20;
	iGemsCollected = 0;

	FullPower = 100.0f;
	Power = FullPower;
	PowerPercentage = Power / FullPower;
	PreviousPower = PowerPercentage;
	PowerValue = 0.0f;
	bCanHit = true;

	if (PowerCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("SetPowerValue"));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SetPowerState") });
		Timeline.AddInterpFloat(PowerCurve, TimelineCallback);
		Timeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
		
	}
	UE_LOG(LogClass, Log, TEXT("BeginPlay"), iGemsCollected);
}

void ABreakingBatPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
}

float ABreakingBatPlayerState::GetHealth()
{
	return HealthPercentage;
	
}

float ABreakingBatPlayerState::GetPower()
{
	return PowerPercentage;
}

void ABreakingBatPlayerState::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	PreviousHealth = HealthPercentage;
	HealthPercentage = Health / FullHealth;
}

void ABreakingBatPlayerState::UpdatePower()
{
	PreviousPower = PowerPercentage;
	PowerPercentage = Power / FullPower;
	PowerValue = 1.0f;
	Timeline.PlayFromStart();
}

FText ABreakingBatPlayerState::GetHealthIntText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPText = FText::FromString(HealthHUD);
	return HPText;
}

FText ABreakingBatPlayerState::GetPowerIntText()
{
	int32 PP = FMath::RoundHalfFromZero(PowerPercentage*FullPower);
	FString PPS = FString::FromInt(PP);
	FString FullPPS = FString::FromInt(FullPower);
	FString PowerHUD = PPS + FString(TEXT("/")) + FullPPS;
	FText PPText = FText::FromString(PowerHUD);
	return PPText;
}

void ABreakingBatPlayerState::DamageTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABreakingBatPlayerState::SetDamageState, 2.0f, false);
}

void ABreakingBatPlayerState::SetDamageState()
{
	SetCanBeDamaged(true);
}

void ABreakingBatPlayerState::SetPowerValue()
{
	TimelineValue = Timeline.GetPlaybackPosition();
	CurveFloatValue = PreviousPower + PowerValue * PowerCurve->GetFloatValue(TimelineValue);
	Power = CurveFloatValue * FullHealth;
	Power = FMath::Clamp(Power, 0.0f, FullPower);
	PowerPercentage = CurveFloatValue;
	PowerPercentage = FMath::Clamp(PowerPercentage, 0.0f, 1.0f);
}

void ABreakingBatPlayerState::SetPowerState()
{
	bCanHit = true;
	PowerValue = 0.0f;
	ABreakingBatCharacter* playerCharacter = Cast< ABreakingBatCharacter>(UGameplayStatics().GetPlayerCharacter(this, 0));
	if (playerCharacter)
		playerCharacter->HandleBatMaterialChange(BatDefaultMaterial);
}

void ABreakingBatPlayerState::SetPowerChange(float PowerChange)
{
	bCanHit = false;
	PreviousPower = PowerPercentage;
	PowerValue = (PowerChange / FullPower);
	ABreakingBatCharacter* playerCharacter = Cast< ABreakingBatCharacter>(UGameplayStatics().GetPlayerCharacter(this, 0));
	if (playerCharacter)
		playerCharacter->HandleBatMaterialChange(BatNoPowerMaterial);
	Timeline.PlayFromStart();
}

void ABreakingBatPlayerState::HandleOnHit()
{
	Timeline.Stop();
	GetWorldTimerManager().ClearTimer(TimerHandle);
	SetPowerChange(-20.0f);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABreakingBatPlayerState::UpdatePower, 5.0f, false);
}
