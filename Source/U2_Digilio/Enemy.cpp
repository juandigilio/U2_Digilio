// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
//#include <SideScrollingPlayerController.cpp>
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Player) return; 
	
	LookAtPlayer(DeltaTime);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

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

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::SetIlluminated(bool bNewState)
{
	bIsIlluminated = bNewState;
}

void AEnemy::LookAtPlayer(float DeltaTime)
{
	FVector ToPlayer = Player->GetActorLocation() - GetActorLocation(); 
	FRotator LookAtRotation = ToPlayer.Rotation(); 
	FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, DeltaTime, RotationSpeed); 

	SetActorRotation(SmoothRotation); 

	FollowPlayer(DeltaTime, ToPlayer);
}

void AEnemy::FollowPlayer(float DeltaTime, FVector ToPlayer)
{
	if (bIsIlluminated) 
	{ 
		FVector Direction = ToPlayer.GetSafeNormal(); 
		AddMovementInput(Direction, MoveSpeed * DeltaTime); 
	}
}


