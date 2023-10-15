// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_GameInstance.h"
#include "Esc_SaveGame.h"
#include "Kismet/GameplayStatics.h"



UEsc_GameInstance::UEsc_GameInstance()
{
    SaveGameSlotName = "SaveGameExample";
}

void UEsc_GameInstance::LoadGame()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0);
	 SaveGameObject = Cast<UEsc_SaveGame>(LoadedGame);

     if (!SaveGameObject)
     {

         // Instantiate a new SaveGame object
         SaveGameObject = Cast<UEsc_SaveGame>(UGameplayStatics::CreateSaveGameObject(UEsc_SaveGame::StaticClass()));

         // Call SaveGameToSlot to serialize and save our SaveGameObject with name: <SaveGameSlotName>.sav
         UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);

     }

}

void UEsc_GameInstance::SaveGame()
{
   
    // Call SaveGameToSlot to serialize and save our SaveGameObject with name: <SaveGameSlotName>.sav
    UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);
}

void UEsc_GameInstance::OnStart()
{
    Super::OnStart();
    LoadGame();
}
