// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeGameModeBase.h"
#include "Esc_MainMenu_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API AEsc_MainMenu_GameMode : public AEscapeGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuWidgetClass = nullptr;

	class UUserWidget* MainMenuWidget = nullptr;

	virtual void BeginPlay() override;
};
