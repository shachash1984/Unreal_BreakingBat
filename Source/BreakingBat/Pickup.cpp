// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create the static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);
	PickupMesh->SetRelativeLocation(FVector::ZeroVector);

}

UStaticMeshComponent * APickup::GetMesh()
{
	return PickupMesh;
}

int APickup::GetScoreValue()
{
	return iScoreValue;
}

void APickup::SetScoreValue(int newValue)
{
	iScoreValue = newValue;
}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool active)
{
	bIsActive = active;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnCollected_Implementation()
{
	//FString PickupDebugString = GetName();
}

