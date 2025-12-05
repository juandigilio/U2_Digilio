#include "Scripts/U2_PlayerState.h"
#include "EngineUtils.h"
#include "Coin.h"

AU2_PlayerState::AU2_PlayerState()
{
	CollectedCoins = 0;
	Health = 100.f;

	FlashlightEnergy = MaxFlashlightEnergy;
}

void AU2_PlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<ACoin> It(GetWorld()); It; ++It)
	{
		ACoin* Coin = *It;
		if (Coin)
		{
			Coin->OnCoinCollected.AddDynamic(this, &AU2_PlayerState::OnCoinCollected);
		}
	}
}


void AU2_PlayerState::AddCoin()
{
	CollectedCoins++;
	OnStatsChanged.Broadcast();
}

void AU2_PlayerState::ApplyDamage(float Amount)
{
	Health -= Amount;
	if (Health < 0) Health = 0;
	OnStatsChanged.Broadcast();
}

void AU2_PlayerState::DrainEnergy(float DeltaTime)
{
	FlashlightEnergy -= EnergyDrainRate * DeltaTime;

	if (FlashlightEnergy < 5000)
		FlashlightEnergy = 5000;
	
	OnStatsChanged.Broadcast();
}

void AU2_PlayerState::RechargeEnergy(float DeltaTime)
{
	FlashlightEnergy += EnergyRechargeRate * DeltaTime;

	if (FlashlightEnergy > MaxFlashlightEnergy)
		FlashlightEnergy = MaxFlashlightEnergy;

	OnStatsChanged.Broadcast();
}

bool AU2_PlayerState::HasEnergy() const
{
	return FlashlightEnergy > 0.f;
}

float AU2_PlayerState::GetEnergyPercent() const
{
	return FlashlightEnergy / MaxFlashlightEnergy;
}

void AU2_PlayerState::OnCoinCollected()
{
	AddCoin();

	UE_LOG(LogTemp, Warning, TEXT("PlayerState: Coin collected! Total: %d"), CollectedCoins);
}

void AU2_PlayerState::SetTotalCoins(int32 total)
{
	TotalCoins = total;
}
