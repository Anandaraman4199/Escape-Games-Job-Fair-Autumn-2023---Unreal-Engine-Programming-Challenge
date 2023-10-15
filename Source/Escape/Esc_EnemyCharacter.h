// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Esc_BaseCharacter.h"
#include "Esc_EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API AEsc_EnemyCharacter : public AEsc_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEsc_EnemyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"))
	class UEsc_Enemy_DataAsset* DataAsset = nullptr;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* MarkerWidget = nullptr;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* HealthWidget = nullptr;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* AttackBox = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<class UEsc_PickUp_DataAsset*> PickUpDataAssets;

	class AEsc_PlayerCharacter* Player = nullptr;

	class UEsc_GameInstance* GameInstance = nullptr;

	FString Name = "";

	bool isTarget = false;

	bool isAttacking = false;

	FTimerHandle TargetTimerHandle, AttackTimerHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void SetAsTarget();

	void RemoveTarget();

	void Attacking();

	virtual float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAttackBoxBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAttackBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SpawnPickUp(UEsc_PickUp_DataAsset* DataAsset);

	void InstantKill();

	void Dead();
};
