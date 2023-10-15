// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_GameplayLevel_GameMode.h"
#include "Esc_EnemyCharacter.h"
#include "Esc_PlayerCharacter.h"
#include "Esc_Enemy_DataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Esc_BlueprintClassManager.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

AEsc_GameplayLevel_GameMode::AEsc_GameplayLevel_GameMode()
{
	BPmanager = Cast<AEsc_BlueprintClassManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEsc_BlueprintClassManager::StaticClass()));
	if (BPmanager) {
		DefaultPawnClass = BPmanager->PlayerCharacterBP;
	}

	
}

void AEsc_GameplayLevel_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPmanager->EnemySpawnPointsActor, EnemySpawnPoints);

	HUD = CreateWidget(GetWorld(), BPmanager->PlayerHUD);
	if (HUD) {
		HUD->AddToViewport();
	}


	FTransform SpawnTransform;
	SpawnTransform.SetLocation(FVector((0.000000,450.000000,-367.999329)));
	AEsc_EnemyCharacter* Enemy = Cast<AEsc_EnemyCharacter>(GetWorld()->SpawnActorDeferred<AEsc_EnemyCharacter>(BPmanager->EnemyCharacterBP,
		SpawnTransform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));

	if (Enemy) {
		Enemy->DataAsset = BPmanager->EnemyDataAssets[0];
		UGameplayStatics::FinishSpawningActor(Enemy, SpawnTransform);
	}


	GetWorld()->GetTimerManager().SetTimer(SpawnWaveHandle,this, &AEsc_GameplayLevel_GameMode::SpawnWave, 1, true, -1);

}

void AEsc_GameplayLevel_GameMode::SpawnEnemy(UEsc_Enemy_DataAsset* DataAsset)
{
	FTransform SpawnTransform = EnemySpawnPoints[rand() % EnemySpawnPoints.Num()]->GetTransform();
	AEsc_EnemyCharacter* Enemy = Cast<AEsc_EnemyCharacter>(GetWorld()->SpawnActorDeferred<AEsc_EnemyCharacter>(BPmanager->EnemyCharacterBP,
		SpawnTransform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));

	if (Enemy) {
		Enemy->DataAsset = DataAsset;
		UGameplayStatics::FinishSpawningActor(Enemy, SpawnTransform);
	}
}

void AEsc_GameplayLevel_GameMode::SpawnWave()
{


	if (NoOfEnemies == 0) {

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Red, TEXT("WPRLO"));
		for (int i = 0; i < (Wave * 3); i++) {
			SpawnEnemy(BPmanager->EnemyDataAssets[0]);
		}
		for (int i = 0; i < (Wave * 2); i++) {
			SpawnEnemy(BPmanager->EnemyDataAssets[1]);
		}
		for (int i = 0; i < (Wave * 1); i++) {
			SpawnEnemy(BPmanager->EnemyDataAssets[2]);
		}
		Wave++;
	}

}



