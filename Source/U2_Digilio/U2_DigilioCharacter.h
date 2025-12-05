// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Scripts/U2_PlayerState.h"
#include "U2_DigilioCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class AEnemy;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(Blueprintable)
class AU2_DigilioCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleFlashlightAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flashlight")
	class USpotLightComponent* Flashlight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flashlight")
	float RaycastDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flashlight")
	float SphereRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flashlight")
	float ConoAngulo   = 15.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flashlight")
	int   RaysX = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flashlight")
	int   RaysY = 3;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void ToggleFlashlight(const FInputActionValue& Value);
	void SetPlayerState();

public:

	AU2_DigilioCharacter();	

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void TakeDamage(float DamageAmount);

private:

	UPROPERTY()
	TArray<AEnemy*> EnemiesInLevel;

	UPROPERTY()
	AU2_PlayerState* CachedPlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flashlight", meta=(AllowPrivateAccess="true"))
	float MinFlashlightIntensity = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta=(AllowPrivateAccess="true"))
	float CurrentHealth = 100.f;
	
	float InitialFlashlightIntensity = 100000.f;
	bool bIlluminatingEnemy;
	bool bIsDead = false;
	
	bool CheckEnemyIllumination();
	void HandleFlashlight(float DeltaTime);
	void FindAllEnemies();
	void HandleDeath();
};

