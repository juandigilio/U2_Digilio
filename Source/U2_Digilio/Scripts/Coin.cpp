
#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);

	AuraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AuraMesh"));
	AuraMesh->SetupAttachment(RootComponent);
	AuraMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WasCollected = false;
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	if (AuraMesh)
	{
		UMaterialInstanceDynamic* DynMat = AuraMesh->CreateAndSetMaterialInstanceDynamic(0);

		if (DynMat)
		{
			DynMat->SetScalarParameterValue("GlowIntensity", 1.f);
		}

		AuraMaterial = AuraMesh->CreateAndSetMaterialInstanceDynamic(0);
		if (AuraMaterial)
		{
			AuraMaterial->SetScalarParameterValue("GlowIntensity", 1.f);
		}
	}
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!WasCollected)
	{
		AddActorLocalRotation(FRotator(0.f, 0.f, RotationSpeed * DeltaTime));

		if (AuraMaterial)
		{
			float Glow = 1.5f + 0.5f * FMath::Sin(GetWorld()->TimeSeconds * 5.f);
			AuraMaterial->SetScalarParameterValue("GlowIntensity", Glow);
		}
	}
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (WasCollected) return;

	if (OtherActor && OtherActor != this && OtherActor->IsA(ACharacter::StaticClass()))
	{
		WasCollected = true;

		AuraMesh->SetVisibility(false);
		Mesh->SetVisibility(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		UE_LOG(LogTemp, Warning, TEXT("Moneda colectada!"));
	}
}
