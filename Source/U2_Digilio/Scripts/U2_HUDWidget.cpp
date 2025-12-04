#include "U2_HUDWidget.h"
#include "U2_PlayerState.h"
#include "GameFramework/PlayerController.h"
//#include "Components/ProgressBar.h"


void UU2_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	PlayerStateRef = PC->GetPlayerState<AU2_PlayerState>();
	if (!PlayerStateRef) return;

	PlayerStateRef->OnStatsChanged.AddDynamic(this, &UU2_HUDWidget::UpdateStats);
	UpdateStats();
}

void UU2_HUDWidget::UpdateStats()
{
	if (!PlayerStateRef) return;

	if (PB_Health)
	{
		float HealthPercent = PlayerStateRef->Health / 100.f;
		PB_Health->SetPercent(HealthPercent);
	}

	if (PB_Energy)
	{
		float EnergyPercent = PlayerStateRef->GetEnergyPercent();
		PB_Energy->SetPercent(EnergyPercent);
	}

	/*if (RT_Coins)
	{
		RT_Coins->SetText(FText::AsNumber(PlayerStateRef->CollectedCoins));
	}*/
}
