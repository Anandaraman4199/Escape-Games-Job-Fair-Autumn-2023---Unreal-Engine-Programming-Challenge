// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_MainMenu_Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Esc_GameInstance.h"
#include "Esc_SaveGame.h"

void UEsc_MainMenu_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	QuitGameButton->OnClicked.AddDynamic(this, &UEsc_MainMenu_Widget::QuitGame);
	StartGameButton->OnClicked.AddDynamic(this, &UEsc_MainMenu_Widget::StartGame);

	GameInstance = Cast<UEsc_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UEsc_MainMenu_Widget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	
	HighScoreValue->SetText(FText::FromString(FString::FromInt(int(GameInstance->SaveGameObject->HighScore))));
}

void UEsc_MainMenu_Widget::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "GameplayLevel");
}

void UEsc_MainMenu_Widget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}
