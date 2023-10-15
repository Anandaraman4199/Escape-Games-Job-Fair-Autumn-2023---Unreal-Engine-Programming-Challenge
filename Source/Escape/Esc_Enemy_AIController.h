// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Esc_Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API AEsc_Enemy_AIController : public AAIController
{
	GENERATED_BODY()

public:
	
	AEsc_Enemy_AIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
