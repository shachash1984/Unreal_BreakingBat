// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakingBatHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ABreakingBatHUD::ABreakingBatHUD()
{
	/*static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/Textures/Crosshair"));
	CrosshairTex = CrosshairTexObj.Object;*/

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/UMG/WBP_HUD"));
	if (HealthBarObj.Class != NULL)
	{
		HUDWidgetClass = HealthBarObj.Class;
	}
	
	
}

void ABreakingBatHUD::DrawHUD()
{
	Super::DrawHUD();

	//Draw very simple crosshair

	////find center of the canvas
	//const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY*0.5f);

	//// offset by half the texture's dimension so that the center of the texture aligns with the center of the canvas
	//const FVector2D CrosshairDrawPosition(Center.X, Center.Y + 20.0f);

	////draw the crosshair
	//FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem(TileItem);
}

void ABreakingBatHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport(1);
		}
	}
}

