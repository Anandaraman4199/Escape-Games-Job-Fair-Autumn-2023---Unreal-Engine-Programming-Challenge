// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Esc_MainMenu_Widget.generated.h"


/**
 * 
 */
UCLASS()
class ESCAPE_API UEsc_MainMenu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	class UEsc_GameInstance* GameInstance;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HighScoreValue;
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
};
