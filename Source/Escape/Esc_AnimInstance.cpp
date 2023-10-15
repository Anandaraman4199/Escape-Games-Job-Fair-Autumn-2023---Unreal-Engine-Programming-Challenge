// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_AnimInstance.h"
#include "Esc_PlayerCharacter.h"
#include "Esc_EnemyCharacter.h"

UEsc_AnimInstance::UEsc_AnimInstance()
{
	OwningActor = nullptr;
	Speed = 0;
	OwningPlayer = nullptr;
	OwningEnemy = nullptr;
	OwningActor = nullptr;
	Direction=0;
	RotationDirection=0;
	bRotating = false;
	bShooting=false;
	bReloading = false;
	bIsAttacking = false;
	LeftHandIKPosition = FVector(0,0,0);
	IKAlpha = 0;

}

UEsc_AnimInstance::~UEsc_AnimInstance()
{

}

void UEsc_AnimInstance::NativeInitializeAnimation()
{
	OwningActor = GetOwningActor();
	OwningPlayer = Cast<AEsc_PlayerCharacter>(OwningActor);
	OwningEnemy = Cast<AEsc_EnemyCharacter>(OwningActor);

}

void UEsc_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Speed = OwningActor->GetVelocity().Size2D();
	Direction = CalculateDirection(OwningActor->GetVelocity(), OwningActor->GetActorRotation());
	
	if (OwningPlayer)
	{
		bRotating = OwningPlayer->bRotating;
		RotationDirection = OwningPlayer->RotationDirection;
		LeftHandIKPosition = OwningPlayer->GetLeftHandIKLocation();
		bShooting = OwningPlayer->isShooting();
		bReloading = OwningPlayer->isReloading();
		IKAlpha = ((Speed > 0) && (!bReloading)) ? 1 : 0;
	}

	if (OwningEnemy) {
		bIsAttacking = OwningEnemy->isAttacking;
	}
}
