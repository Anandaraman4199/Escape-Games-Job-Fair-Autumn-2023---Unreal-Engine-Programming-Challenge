// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_Gun.h"
#include "Esc_EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Esc_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEsc_Gun::AEsc_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	SetRootComponent(GunMesh);

}

// Called when the game starts or when spawned
void AEsc_Gun::BeginPlay()
{
	Super::BeginPlay();
	NoOfRemainingBullets = MaxBullets;
	
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &AEsc_Gun::LineTrace, 0.1, true, -1);
}

// Called every frame
void AEsc_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AEsc_Gun::StartFire()
{
	bFiring = true;
	OnFire();
}

void AEsc_Gun::StopFire()
{
	bFiring = false;
}

void AEsc_Gun::Reload()
{
	NoOfRemainingBullets = MaxBullets;
	bReloading = false;
}

void AEsc_Gun::LineTrace()
{

	if (GunMesh) {
	
		FVector Start = GunMesh->GetSocketLocation(TEXT("MuzzleFlash"));

		if (OwnerPlayer) {

			//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Cyan, TEXT("Tracing"));

			FVector End = Start + (OwnerPlayer->GetActorForwardVector() * 1250);

			FCollisionQueryParams CollisionParams;

			bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Pawn, CollisionParams);

			if (isHit) {

				AEsc_EnemyCharacter* targetEnemy = Cast<AEsc_EnemyCharacter>(OutHit.GetActor());
				if (targetEnemy) {
					Cast<AEsc_EnemyCharacter>(OutHit.GetActor())->SetAsTarget();
					StartFire();
				}
				else {
					StopFire();
				}
				
				
			}
			else {
				StopFire();
			}

		}
		
	}

}

void AEsc_Gun::OnFire()
{
	if (bFiring) {

		if (NoOfRemainingBullets) {

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				MuzzleFlashParticle,
				GunMesh->GetSocketTransform(TEXT("MuzzleFlash")));

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				ShellEjectParticle,
				GunMesh->GetSocketTransform(TEXT("ShellEjectSocket")));

			NoOfRemainingBullets--;
			if (OutHit.GetActor()) {
				if (Cast<AEsc_EnemyCharacter>(OutHit.GetActor())) {
					UGameplayStatics::ApplyDamage(OutHit.GetActor(), 10, OwnerPlayer->Controller, this, UDamageType::StaticClass());
				}
			}
			if (!NoOfRemainingBullets) {
				FTimerHandle ReloadTimerHandle;
				bReloading = true;
				GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AEsc_Gun::Reload, ReloadTime, false);

			}

		}

		GetWorld()->GetTimerManager().SetTimer(fireTimerHandle, this, &AEsc_Gun::OnFire, 1/RateOfFire, false);

	}
}

