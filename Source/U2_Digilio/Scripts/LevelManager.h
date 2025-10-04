
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.h"
#include "LevelManager.generated.h"

UCLASS()
class U2_DIGILIO_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Setup")
	TArray<ACoin*> Coins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Setup")
	AActor* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Setup")
	FVector DoorOffset = FVector(200.f, 0.f, 0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Setup")
	bool bAllCoinsCollected = false;

	ALevelManager();
	virtual void Tick(float DeltaTime) override;

private:
	bool bDoorMoved = false;

protected:
	
	virtual void BeginPlay() override;
};
