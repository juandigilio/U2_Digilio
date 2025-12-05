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
	
	PB_Health->SetPercent(PlayerStateRef->Health / 100.f);

	PB_Energy->SetPercent(PlayerStateRef->GetEnergyPercent());

	if (Coins)
	{
		FString Text = FString::Printf(TEXT("%d / %d"),
			PlayerStateRef->CollectedCoins,
			PlayerStateRef->TotalCoins);

		Coins->SetText(FText::FromString(Text));
	}
}
