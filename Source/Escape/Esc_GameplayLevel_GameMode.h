// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeGameModeBase.h"
#include "Esc_GameplayLevel_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API AEsc_GameplayLevel_GameMode : public AEscapeGameModeBase
{
	GENERATED_BODY()


private:
	class AEsc_BlueprintClassManager* BPmanager = nullptr;

	class UUserWidget* HUD = nullptr;

	TArray<AActor*> EnemySpawnPoints;




	FTimerHandle SpawnWaveHandle;




public:

	int Wave = 1;

	int NoOfEnemies = 0;

	AEsc_GameplayLevel_GameMode();

	virtual void BeginPlay() override;

	void SpawnEnemy(class UEsc_Enemy_DataAsset* DataAsset);

	void SpawnWave();


};
