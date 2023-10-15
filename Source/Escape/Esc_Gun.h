// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Esc_Gun.generated.h"

UCLASS()
class ESCAPE_API AEsc_Gun : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEsc_Gun();

	FHitResult OutHit;

	bool bFiring = false;

	bool bReloading = false;

	float ReloadTime = 4;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(EditAnywhere)
	float RateOfFire = 0;
	
	int NoOfRemainingBullets = 0;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlashParticle = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ShellEjectParticle = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxBullets = 0;

	FTimerHandle fireTimerHandle, TraceTimerHandle;

	class AEsc_PlayerCharacter* OwnerPlayer = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnFire();

	void StartFire();

	void StopFire();

	void Reload();

	void LineTrace();

};
