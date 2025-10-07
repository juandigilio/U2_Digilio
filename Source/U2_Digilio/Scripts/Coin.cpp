
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

	SetTriggerMesh();
	SetBoxCollider();
	SetAuraMesh();

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

void ACoin::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (!WasCollected)
	{
		AddActorLocalRotation(FRotator(0.f, 0.f, RotationSpeed * deltaTime));

		if (AuraMaterial)
		{
			float Glow = 2.5f + 2.5f * FMath::Sin(GetWorld()->TimeSeconds * 5.f);
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
		SetOff();
	}
}

void ACoin::SetOff()
{
	WasCollected = true;

	AuraMesh->SetVisibility(false);
	Mesh->SetVisibility(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Warning, TEXT("Moneda colectada!"));
}

void ACoin::SetTriggerMesh()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);
}

void ACoin::SetBoxCollider()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

void ACoin::SetAuraMesh()
{
	AuraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AuraMesh"));
	AuraMesh->SetupAttachment(RootComponent);
	AuraMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


