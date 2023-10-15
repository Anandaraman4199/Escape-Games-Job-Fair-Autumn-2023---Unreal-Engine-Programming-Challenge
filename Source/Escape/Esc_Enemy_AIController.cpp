// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_Enemy_AIController.h"
#include "Esc_EnemyCharacter.h"
#include "Esc_Enemy_DataAsset.h"
#include "Kismet/GameplayStatics.h"

AEsc_Enemy_AIController::AEsc_Enemy_AIController()
{
	
}

void AEsc_Enemy_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEsc_Enemy_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 50);

}
