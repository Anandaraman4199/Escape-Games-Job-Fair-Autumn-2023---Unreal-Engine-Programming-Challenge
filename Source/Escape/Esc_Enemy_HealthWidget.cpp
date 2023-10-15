// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_Enemy_HealthWidget.h"
#include "Components/ProgressBar.h"
#include "Esc_EnemyCharacter.h"

void UEsc_Enemy_HealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UEsc_Enemy_HealthWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if (OwningEnemy) {
		
		HealthBar->SetPercent(OwningEnemy->Health / OwningEnemy->MaxHealth);
	}
	
}
