// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Esc_PickUp_DataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_PickUp_DataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name="";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Xp=0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health=0;
	
};
