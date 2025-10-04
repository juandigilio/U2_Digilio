


#include "LevelManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineUtils.h"


ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	

	Coins.Empty();

	for (TActorIterator<ACoin> It(GetWorld()); It; ++It)
	{
		Coins.Add(*It);
	}
}

void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAllCoinsCollected)
	{
		bool bAllCollected = true;
		for (ACoin* Coin : Coins)
		{
			if (Coin && !Coin->WasCollected)
			{
				bAllCollected = false;
				break;
			}
		}

		if (bAllCollected)
		{
			bAllCoinsCollected = true;
			if (Door && !bDoorMoved)
			{
				FVector NewLocation = Door->GetActorLocation() + DoorOffset;
				Door->SetActorLocation(NewLocation);
				bDoorMoved = true;

				UE_LOG(LogTemp, Warning, TEXT("Todas las monedas fueron colectadas. ¡Puerta abierta!"));
			}
		}
	}
}

