// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_BaseCharacter.h"

// Sets default values
AEsc_BaseCharacter::AEsc_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 0;
	MaxHealth = 0;
	bDeath = false;

}

// Called when the game starts or when spawned
void AEsc_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEsc_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEsc_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

