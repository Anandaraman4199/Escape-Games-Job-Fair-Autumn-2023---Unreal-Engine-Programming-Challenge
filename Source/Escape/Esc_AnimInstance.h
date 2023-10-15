// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Esc_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	class AEsc_PlayerCharacter* OwningPlayer;
	class AEsc_EnemyCharacter* OwningEnemy;
	AActor* OwningActor;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Actor Details");
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Actor Details");
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Player Details");
	float RotationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Player Details");
	bool bRotating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Player Details");
	bool bShooting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Player Details");
	bool bReloading;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Enemy Details");
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Player Details");
	FVector LeftHandIKPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owning Player Details");
	float IKAlpha = 0 ;


	UEsc_AnimInstance();
	~UEsc_AnimInstance();

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
