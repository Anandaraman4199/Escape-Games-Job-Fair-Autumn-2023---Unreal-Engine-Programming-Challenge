// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Esc_Enemy_HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_Enemy_HealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	class AEsc_EnemyCharacter* OwningEnemy;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
};
