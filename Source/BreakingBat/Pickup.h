// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BREAKINGBAT_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	class UStaticMeshComponent* GetMesh();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	int GetScoreValue();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetScoreValue(int newValue);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool active);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Pickup")
	int iScoreValue;

	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* PickupMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnCollected();
	virtual void OnCollected_Implementation();

	
};
