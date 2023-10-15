// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Esc_PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	class AEsc_GameplayLevel_GameMode* thisGamemode;

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* XPValue;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NoOfBulletRemaining;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ReloadingText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreValue;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WaveValue;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	class AEsc_Gun* PlayerGun;

	class AEsc_PlayerCharacter* PlayerCharacter;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	
};
