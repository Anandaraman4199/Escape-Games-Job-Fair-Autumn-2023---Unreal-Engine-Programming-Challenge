// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Esc_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UEsc_SaveGame();

	UPROPERTY(BlueprintReadWrite, Category = "Player Info")
	float HighScore = 0;
	
};
