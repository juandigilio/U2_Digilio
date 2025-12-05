


#include "LevelManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/DirectionalLightComponent.h"


ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bAllCoinsCollected = false;
}

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	SetLights();

	CachedPlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<AU2_PlayerState>();

	for (ACoin* coin : coins)
	{
		if (coin)
		{
			totalCoins++;
			coin->OnCoinCollected.AddDynamic(this, &ALevelManager::OnCoinCollectedHandler);
		}
	}

	CachedPlayerState->SetTotalCoins(totalCoins);
}

void ALevelManager::SetLights()
{
	for (ADirectionalLight* light : statueLights)
	{
		light->GetLightComponent()->SetIntensity(0.0f);
	}

	mainLightIntensity = mainLight->GetLightComponent()->Intensity;
}

void ALevelManager::CheckDoorStatus(float deltaTime)
{
	if (bAllCoinsCollected)
	{
		if (door && !bDoorMoved)
		{
			doorStartLocation = door->GetActorLocation();
			doorTargetLocation = doorStartLocation + doorOffset;
			bIsDoorOpening = true;
			bDoorMoved = true;

			UE_LOG(LogTemp, Warning, TEXT("Todas las monedas fueron colectadas. �Abriendo puerta!"));
		}

		MoveDoor(deltaTime);
	}
}

void ALevelManager::SetLightsOn(float deltaTime)
{
	if (bLightsFadingIn)
	{
		auto FadeLight = [&](ADirectionalLight* Light)
		{
			if (!Light) return;
			auto* LightComp = Light->GetLightComponent();
			float CurrentIntensity = LightComp->Intensity;
			float NewIntensity = FMath::FInterpTo(CurrentIntensity, maxLightIntensity, deltaTime, lightFadeSpeed);
			LightComp->SetIntensity(NewIntensity);
		};

		for (ADirectionalLight* light : statueLights)
		{
			FadeLight(light);
		}

		if (statueLights[0] && statueLights[0]->GetLightComponent()->Intensity >= maxLightIntensity - 0.1f)
		{
			bLightsFadingIn = false;
		}
	}
}

void ALevelManager::MoveDoor(float deltaTime)
{
	if (bIsDoorOpening && door)
	{
		FVector currentLocation = door->GetActorLocation();
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, doorTargetLocation, deltaTime, doorMoveSpeed);
		door->SetActorLocation(newLocation);

		if (FVector::Dist(newLocation, doorTargetLocation) < 1.0f)
		{
			bIsDoorOpening = false;
			bLightsFadingIn = true;
		}
	}
}

void ALevelManager::OnCoinCollectedHandler()
{
	collectedCoins++;
	UE_LOG(LogTemp, Warning, TEXT("Coin recogida! Total: %d"), collectedCoins);

	if (collectedCoins >= totalCoins)
	{
		bAllCoinsCollected = true;
	}
}

void ALevelManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	CheckDoorStatus(deltaTime);
	SetLightsOn(deltaTime);
}

