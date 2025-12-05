// Enemy.cpp

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AU2_DigilioCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			TEXT("Player ENCONTRADO"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			TEXT("Player ES NULL!"));
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Player) return;
	
	LookAtPlayer(DeltaTime);

	FVector ToPlayer = Player->GetActorLocation() - GetActorLocation();
	FollowPlayer(DeltaTime, ToPlayer);
	
	float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

	if (Distance <= DamageRadius)
	{
		if (AttackMontage && !IsPlayingRootMotion())
		{
			Player->TakeDamage(DamagePerHit);
			PlayAnimMontage(AttackMontage);
		}
	}
}

void AEnemy::LookAtPlayer(float DeltaTime)
{
	if (!Player) return;

	FVector ToPlayer = Player->GetActorLocation() - GetActorLocation();
	FRotator LookAtRotation = ToPlayer.Rotation();

	FRotator SmoothRotation = FMath::RInterpTo(
		GetActorRotation(),
		LookAtRotation,
		DeltaTime,
		RotationSpeed
	);

	SetActorRotation(SmoothRotation);
}

void AEnemy::FollowPlayer(float DeltaTime, FVector ToPlayer)
{
	if (bIsIlluminated) 
	{ 
		FVector Direction = ToPlayer.GetSafeNormal();
		AddMovementInput(Direction, MoveSpeed * DeltaTime);
	}
}

void AEnemy::SetIlluminated(bool bNewState)
{
	bIsIlluminated = bNewState;
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
