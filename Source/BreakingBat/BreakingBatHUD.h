// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BreakingBatHUD.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGBAT_API ABreakingBatHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ABreakingBatHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Health")
	class UUserWidget* CurrentWidget;
};
