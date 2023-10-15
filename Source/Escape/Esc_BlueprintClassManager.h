// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Esc_BlueprintClassManager.generated.h"

UCLASS()
class ESCAPE_API AEsc_BlueprintClassManager : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEsc_EnemyCharacter> EnemyCharacterBP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEsc_PlayerCharacter> PlayerCharacterBP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerHUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> EnemySpawnPointsActor;

	UPROPERTY(EditAnywhere)
	TArray<class UEsc_Enemy_DataAsset*> EnemyDataAssets;


public:	
	// Sets default values for this actor's properties
	AEsc_BlueprintClassManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
