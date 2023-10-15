// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Esc_BaseCharacter.h"
#include "Esc_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API AEsc_PlayerCharacter : public AEsc_BaseCharacter
{
	GENERATED_BODY()



private:

	bool bAiming = false;

	FRotator DesiredRotation;

	// Stores the ref to default camera spawned by the player camera manager
	ACameraActor* FollowCamera = nullptr;

	// Calculate and Stores the movement vectors for both axis
	FVector FwdMovementVec, RgtMovementVec;

public:

	int XP = 0;

	float Score = 0;

	bool bRotating = false;
	float RotationDirection=0;

	UPROPERTY(EditAnywhere)
	float RotationRate=0;

	UPROPERTY(EditAnywhere)
	float CameraToPlayerDistance = 500;

	UPROPERTY(EditAnywhere)
	UChildActorComponent* GunHolderComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* RotationWidget = nullptr;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* DesiredRotationWidget = nullptr;


	// Sets default values for this character's properties
	AEsc_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the MoveForward input pressed
	void MoveForward(float axis);

	// Called when the MoveRight input pressed
	void MoveRight(float axis);

	// Called when the Aim input pressed
	void AimPressed();

	// Called when the Aim input released
	void AimReleased();

	// Called every frame to update the player movement
	void UpdateMovement();

	// Called every frame at the end of Tick to Update Camera Position
	void UpdateCamera();

	// Called every frame to update the player rotation
	void UpdateRotation(float DeltaTime);

	FVector GetLeftHandIKLocation();

	void InstantKill();

	bool isShooting();

	bool isReloading();

	void MainMenu();

	void PickUp(int inXP, int inHealth);

	void NoReloadTime();

	void ReloadTimeReset();

	virtual float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
