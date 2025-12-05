// Enemy.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "U2_DigilioCharacter.h"
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

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float RotationSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	float DamagePerHit = 10.f;

	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	float DamageRadius = 120.f;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* AttackMontage;

	virtual void BeginPlay() override;

private:

	bool bIsIlluminated = false;

	UPROPERTY()
	AU2_DigilioCharacter* Player = nullptr;

	void LookAtPlayer(float DeltaTime);
	void FollowPlayer(float DeltaTime, FVector ToPlayer);
};
