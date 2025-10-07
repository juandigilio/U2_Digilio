
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Coin.h"
#include "LevelManager.generated.h"

UCLASS()
class U2_DIGILIO_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Setup")
	TArray<ACoin*> coins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Setup")
	AActor* door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Setup")
	FVector doorOffset = FVector(200.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Door")
	float doorMoveSpeed = 70.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Setup")
	bool bAllCoinsCollected = false;

	UPROPERTY(EditAnywhere, Category = "Lighting")
	TArray<ADirectionalLight*> directionalLights;

	UPROPERTY(EditAnywhere, Category = "Lighting")
	float lightFadeSpeed = 4.0f;

	UPROPERTY(EditAnywhere, Category = "Lighting")
	float maxLightIntensity = 150.0f;

	ALevelManager();
	virtual void Tick(float deltaTime) override;

private:
	FVector doorStartLocation;
	FVector doorTargetLocation;
	bool bDoorMoved = false;
	bool bIsDoorOpening = false;
	bool bLightsFadingIn = false;

	void SetLightsOff();
	void CheckCollectedCoins();
	void CheckDoorStatus(float deltaTime);
	void SetLightsOn(float deltaTime);
	void MoveDoor(float deltaTime);

protected:
	
	virtual void BeginPlay() override;
};
