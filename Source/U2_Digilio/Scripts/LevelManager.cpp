


#include "LevelManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/DirectionalLightComponent.h"


ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	SetLightsOff();

	/*coins.Empty();

	for (TActorIterator<ACoin> It(GetWorld()); It; ++It)
	{
		coins.Add(*It);
	}*/
}

void ALevelManager::SetLightsOff()
{
	for (ADirectionalLight* light : directionalLights)
	{
		light->GetLightComponent()->SetIntensity(0.0f);
	}
}

void ALevelManager::CheckCollectedCoins()
{
	if (!bAllCoinsCollected)
	{
		bAllCoinsCollected = true;

		for (ACoin* coin : coins)
		{
			if (coin && !coin->WasCollected)
			{
				bAllCoinsCollected = false;
				break;
			}
		}
	}
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

			UE_LOG(LogTemp, Warning, TEXT("Todas las monedas fueron colectadas. ¡Abriendo puerta!"));
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

		for (ADirectionalLight* light : directionalLights)
		{
			FadeLight(light);
		}

		if (directionalLights[0] && directionalLights[0]->GetLightComponent()->Intensity >= maxLightIntensity - 0.1f)
		{
			bLightsFadingIn = false;

			//UE_LOG(LogTemp, Warning, TEXT("Luces encendidas al máximo."));
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
			//UE_LOG(LogTemp, Warning, TEXT("Puerta completamente abierta."));
		}
	}
}

void ALevelManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	CheckCollectedCoins();
	CheckDoorStatus(deltaTime);
	SetLightsOn(deltaTime);
}

