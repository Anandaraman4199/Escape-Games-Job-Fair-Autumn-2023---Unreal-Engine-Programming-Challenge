// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_PlayerHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Esc_PlayerCharacter.h"
#include "Esc_Gun.h"
#include "Esc_GameplayLevel_GameMode.h"

void UEsc_PlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AEsc_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	PlayerGun = Cast<AEsc_Gun>(PlayerCharacter->GunHolderComponent->GetChildActor());

	thisGamemode = Cast<AEsc_GameplayLevel_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UEsc_PlayerHUDWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{

	Super::NativeTick(MyGeometry, DeltaTime);
	if (PlayerCharacter) {
		HealthBar->SetPercent(PlayerCharacter->Health / PlayerCharacter->MaxHealth);
		XPValue->SetText(FText::FromString(FString::FromInt(PlayerCharacter->XP)));
		if (PlayerGun) {

			NoOfBulletRemaining->SetText(FText::FromString(FString::FromInt(PlayerGun->NoOfRemainingBullets)));

			if (PlayerGun->bReloading) {
				ReloadingText->SetVisibility(ESlateVisibility::Visible);
			}
			else {
				ReloadingText->SetVisibility(ESlateVisibility::Hidden);
			}
		}

		ScoreValue->SetText(FText::FromString(FString::FromInt(int(PlayerCharacter->Score))));

	}

	WaveValue->SetText(FText::FromString(FString::FromInt(thisGamemode->Wave - 1)));
}
