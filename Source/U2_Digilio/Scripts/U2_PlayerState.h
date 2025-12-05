#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "U2_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsChanged);


UCLASS()
class U2_DIGILIO_API AU2_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AU2_PlayerState();
	

	UPROPERTY(BlueprintAssignable, Category="Stats")
	FOnStatsChanged OnStatsChanged;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	int32 CollectedCoins = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	int32 TotalCoins = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	float Health = 100.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flashlight")
	float FlashlightEnergy = 999999.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flashlight")
	float MaxFlashlightEnergy = 999999.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flashlight")
	float EnergyDrainRate = 300.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flashlight")
	float EnergyRechargeRate = 300.f;
	

	UFUNCTION(BlueprintCallable, Category="Stats")
	void AddCoin();
	
	UFUNCTION(BlueprintCallable, Category="Stats")
	void ApplyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void DrainEnergy(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void RechargeEnergy(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category="Flashlight")
	bool HasEnergy() const;

	UFUNCTION(BlueprintCallable, Category="Flashlight")
	float GetEnergyPercent() const;

	UFUNCTION()
	void OnCoinCollected();
	UFUNCTION()
	void SetTotalCoins(int32 total);

	

protected:
	
	virtual void BeginPlay() override;
};
