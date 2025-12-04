#include "Scripts/U2_PlayerState.h"

AU2_PlayerState::AU2_PlayerState()
{
	CollectedCoins = 0;
	Health = 100.f;

	FlashlightEnergy = MaxFlashlightEnergy;
}

void AU2_PlayerState::AddCoin()
{
	CollectedCoins++;
}

void AU2_PlayerState::ApplyDamage(float Amount)
{
	Health -= Amount;
	if (Health < 0) Health = 0;
}

void AU2_PlayerState::DrainEnergy(float DeltaTime)
{
	FlashlightEnergy -= EnergyDrainRate * DeltaTime;

	if (FlashlightEnergy < 5000)
		FlashlightEnergy = 5000;
}

void AU2_PlayerState::RechargeEnergy(float DeltaTime)
{
	FlashlightEnergy += EnergyRechargeRate * DeltaTime;

	if (FlashlightEnergy > MaxFlashlightEnergy)
		FlashlightEnergy = MaxFlashlightEnergy;
}

bool AU2_PlayerState::HasEnergy() const
{
	return FlashlightEnergy > 0.f;
}

float AU2_PlayerState::GetEnergyPercent() const
{
	return FlashlightEnergy / MaxFlashlightEnergy;
}
