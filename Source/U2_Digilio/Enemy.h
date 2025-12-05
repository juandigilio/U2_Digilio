// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class U2_DIGILIO_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	AEnemy();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetIlluminated(bool bNewState);

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	float RotationSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float Damage = 0.1f;

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual void BeginPlay() override;

private:

	APawn* Player = nullptr;
	bool bIsIlluminated = false;

	void LookAtPlayer(float DeltaTime); 
	void FollowPlayer(float DeltaTime, FVector ToPlayer);
};
