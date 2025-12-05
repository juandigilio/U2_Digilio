// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "U2_HUDWidget.generated.h"

class AU2_PlayerState;

/**
 * 
 */
UCLASS()
class U2_DIGILIO_API UU2_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateStats();

protected:

	UPROPERTY()
	AU2_PlayerState* PlayerStateRef;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_Health;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_Energy;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Coins;
};
