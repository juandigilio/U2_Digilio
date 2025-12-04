// Fill out your copyright notice in the Description page of Project Settings.


#include "Scripts/U2_DigilioHUD.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/U2_HUDWidget.h"


void AU2_DigilioHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
