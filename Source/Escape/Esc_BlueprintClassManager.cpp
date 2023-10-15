// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_BlueprintClassManager.h"

// Sets default values
AEsc_BlueprintClassManager::AEsc_BlueprintClassManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCharacterBP = nullptr;
	PlayerCharacterBP = nullptr;
	PlayerHUD = nullptr;
	EnemySpawnPointsActor = nullptr;
}

// Called when the game starts or when spawned
void AEsc_BlueprintClassManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEsc_BlueprintClassManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

