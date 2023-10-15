// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Esc_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UEsc_GameInstance();

	UPROPERTY(BlueprintReadOnly)
	FString SaveGameSlotName = "";

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	class UEsc_SaveGame* SaveGameObject = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void SaveGame();

	virtual void OnStart() override;
};
