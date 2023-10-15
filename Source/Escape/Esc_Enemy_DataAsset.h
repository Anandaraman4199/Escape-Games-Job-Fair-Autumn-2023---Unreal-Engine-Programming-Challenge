// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Esc_Enemy_DataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_Enemy_DataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UEsc_Enemy_DataAsset();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackRate;


};
