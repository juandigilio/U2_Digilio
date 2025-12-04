// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "U2_DigilioHUD.generated.h"

class UU2_HUDWidget;

/**
 * 
 */
UCLASS()
class U2_DIGILIO_API AU2_DigilioHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UU2_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* HUDWidget;

	virtual void BeginPlay() override;
};
