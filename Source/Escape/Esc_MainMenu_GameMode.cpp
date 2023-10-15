// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_MainMenu_GameMode.h"
#include "Esc_MainMenu_Widget.h"
#include "Kismet/GameplayStatics.h"

void AEsc_MainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	MainMenuWidget = CreateWidget(GetWorld(), MainMenuWidgetClass);
	
	if (MainMenuWidget) {
		MainMenuWidget->AddToViewport();
	}

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	
}
