// Copyright Epic Games, Inc. All Rights Reserved.

#include "U2_DigilioCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SpotLightComponent.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "U2_Digilio.h"
#include "Kismet/GameplayStatics.h"

AU2_DigilioCharacter::AU2_DigilioCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(GetMesh());
	Flashlight->SetRelativeLocation(FVector(0.f, 0.f, 40.f)); // ajustar
	Flashlight->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	Flashlight->Intensity = 100000.f;
	Flashlight->SetInnerConeAngle(15.f);
	Flashlight->SetOuterConeAngle(28.f);
	Flashlight->AttenuationRadius = 630.f;
	Flashlight->SetVisibility(false);

	RaycastDistance = 3000.f;
}

void AU2_DigilioCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AU2_DigilioCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AU2_DigilioCharacter::Look);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AU2_DigilioCharacter::Look);

		EnhancedInputComponent->BindAction(ToggleFlashlightAction, ETriggerEvent::Started, this, &AU2_DigilioCharacter::ToggleFlashlight);
	}
	else
	{
		UE_LOG(LogU2_Digilio, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AU2_DigilioCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckEnemyIllumination();
}

void AU2_DigilioCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FindAllEnemies();
}

void AU2_DigilioCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	DoMove(MovementVector.X, MovementVector.Y);
}

void AU2_DigilioCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AU2_DigilioCharacter::ToggleFlashlight(const FInputActionValue& Value)
{
	if (!Flashlight) return;

	bool bIsOn = Flashlight->IsVisible();
	Flashlight->SetVisibility(!bIsOn);
}

void AU2_DigilioCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AU2_DigilioCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AU2_DigilioCharacter::DoJumpStart()
{
	Jump();
}

void AU2_DigilioCharacter::DoJumpEnd()
{
	StopJumping();
}

void AU2_DigilioCharacter::CheckEnemyIllumination()
{
	for (AEnemy* Enemy : EnemiesInLevel)
	{
		if (Enemy)
			Enemy->SetIlluminated(false);
	}
	
	if (Flashlight && Flashlight->IsVisible())
	{
		FVector Start   = Flashlight->GetComponentLocation();
		FVector Forward = Flashlight->GetForwardVector();
		FVector Right   = GetActorRightVector();
		FVector Up      = GetActorUpVector();

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		auto DoSphereCast = [&](const FVector& End, float Radius)
		{
			FHitResult Hit;
			bool bHit = GetWorld()->SweepSingleByChannel(
				Hit,
				Start,
				End,
				FQuat::Identity,
				ECC_Visibility,
				FCollisionShape::MakeSphere(Radius),
				Params
			);
			
			//DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 0.05f, 0, 1.f);
			//DrawDebugSphere(GetWorld(), End, Radius, 12, FColor::Blue, false, 0.05f);

			if (bHit)
			{
				//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 12.f, 12, FColor::Red, false, 0.2f);

				if (AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor()))
				{
					Enemy->SetIlluminated(true);
				}
			}

			return bHit;
		};
		
		FVector EndCenter = Start + Forward * RaycastDistance;
		DoSphereCast(EndCenter, SphereRadius);

		for (int x = -RaysX; x <= RaysX; x++)
		{
			for (int y = -RaysY; y <= RaysY; y++)
			{
				if (x == 0 && y == 0) continue;

				float AngleX = (x / (float)RaysX) * ConoAngulo;
				float AngleY = (y / (float)RaysY) * ConoAngulo;
				
				FVector Dir = Forward
					+ Right * FMath::Tan(FMath::DegreesToRadians(AngleX))
					+ Up    * FMath::Tan(FMath::DegreesToRadians(AngleY));
			
				Dir = Dir.GetSafeNormal();

				FVector End = Start + Dir * RaycastDistance;

				DoSphereCast(End, SphereRadius * 0.8f);
			}
		}
	}

}

void AU2_DigilioCharacter::FindAllEnemies()
{
	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Found);

	for (AActor* A : Found)
	{
		if (AEnemy* Enemy = Cast<AEnemy>(A))
		{
			EnemiesInLevel.Add(Enemy);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Cargados %d enemigos."), EnemiesInLevel.Num());
}
