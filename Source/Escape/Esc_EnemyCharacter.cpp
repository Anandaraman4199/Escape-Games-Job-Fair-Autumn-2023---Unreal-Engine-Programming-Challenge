// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_EnemyCharacter.h"
#include "Esc_PlayerCharacter.h"
#include "Esc_Enemy_DataAsset.h"
#include "Esc_Enemy_AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Esc_Enemy_HealthWidget.h"
#include "Esc_GameplayLevel_GameMode.h"
#include "Esc_GameInstance.h"
#include "Esc_SaveGame.h"
#include "Esc_PickUp_DataAsset.h"
#include "Esc_PickUp.h"

// Sets default values
AEsc_EnemyCharacter::AEsc_EnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MarkerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MarkerWidget"));
	MarkerWidget->SetupAttachment(GetMesh());

	MarkerWidget->SetVisibility(false);

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetupAttachment(GetMesh());

	HealthWidget->SetVisibility(false);

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->SetupAttachment(GetMesh());
	AttackBox->SetBoxExtent(FVector(125, 100, 32));
	AttackBox->AddRelativeLocation(FVector(0, 100, 100));

	AIControllerClass = AEsc_Enemy_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	Player = (Cast<AEsc_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
	GameInstance = Cast<UEsc_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


}

// Called when the game starts or when spawned
void AEsc_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<AEsc_GameplayLevel_GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->NoOfEnemies++;
	Health = DataAsset->Health;
	MaxHealth = DataAsset->Health;

	Cast<UEsc_Enemy_HealthWidget>(HealthWidget->GetWidget())->OwningEnemy = this;


	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AEsc_EnemyCharacter::OnAttackBoxBeginOverlap);
	AttackBox->OnComponentEndOverlap.AddDynamic(this, &AEsc_EnemyCharacter::OnAttackBoxEndOverlap);

	
}

// Called every frame
void AEsc_EnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MarkerWidget->SetVisibility(isTarget);

	HealthWidget->SetVisibility(isTarget);

}

void AEsc_EnemyCharacter::OnConstruction(const FTransform& Transform)
{

	if (DataAsset) {

		Name = DataAsset->Name;
		GetMesh()->SetSkeletalMesh(DataAsset->Mesh, true);
		GetMesh()->AnimClass = DataAsset->AnimInstance;

		GetCharacterMovement()->MaxWalkSpeed = DataAsset->MovementSpeed;

		if (DataAsset->Name.Contains(TEXT("Heavy_Enemy"))) {
			GetCapsuleComponent()->SetCapsuleSize(125, 125);
			GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -125), FRotator(0, -90, 0));
			HealthWidget->SetRelativeLocation(FVector(0, 0, 275));
		}
		else {
			GetCapsuleComponent()->SetCapsuleSize(100, 100);
			GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100), FRotator(0, -90, 0));
			HealthWidget->SetRelativeLocation(FVector(0, 0, 225));
		}

	}

}

void AEsc_EnemyCharacter::SetAsTarget()
{
	isTarget = true;
	GetWorld()->GetTimerManager().SetTimer(TargetTimerHandle, this, &AEsc_EnemyCharacter::RemoveTarget, 0.125, false, -1);
}

void AEsc_EnemyCharacter::RemoveTarget()
{
	isTarget = false;
}

void AEsc_EnemyCharacter::Attacking()
{
	if (isAttacking) {
		UGameplayStatics::ApplyDamage(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0),
			DataAsset->Damage,
			GetController(),
			this,
			UDamageType::StaticClass());

		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Red, TEXT("ATTACKING"));
	}	
}


float AEsc_EnemyCharacter::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0) {
		Dead();
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEsc_EnemyCharacter::OnAttackBoxBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEsc_PlayerCharacter>(OtherActor)) {
		isAttacking = true;
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AEsc_EnemyCharacter::Attacking, 1 / DataAsset->AttackRate, true, 1);
	}
}

void AEsc_EnemyCharacter::OnAttackBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AEsc_PlayerCharacter>(OtherActor)) {
		isAttacking = false;
	}
}


void AEsc_EnemyCharacter::SpawnPickUp(UEsc_PickUp_DataAsset* PickUpDataAsset)
{
	FTransform SpawnTransform = GetActorTransform();
	auto PickUpActor =  Cast<AEsc_PickUp>(GetWorld()->SpawnActorDeferred<AEsc_PickUp>(AEsc_PickUp::StaticClass(), 
		SpawnTransform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));

	if (PickUpActor) {
		PickUpActor->DataAsset = PickUpDataAsset;
		PickUpActor->FinishSpawning(SpawnTransform);
	}
}

void AEsc_EnemyCharacter::InstantKill()
{
	if (FVector::Dist2D(Player->GetActorLocation(), GetActorLocation()) < 500) {
		Dead();
	}
}

void AEsc_EnemyCharacter::Dead()
{
	bDeath = true;
	Player->Score += DataAsset->Score;
	if (GameInstance) {
		if (Player->Score > GameInstance->SaveGameObject->HighScore) {
			GameInstance->SaveGameObject->HighScore = Player->Score;
			GameInstance->SaveGame();
		}
	}
	Cast<AEsc_GameplayLevel_GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->NoOfEnemies--;
	SpawnPickUp(PickUpDataAssets[rand() % PickUpDataAssets.Num()]);
	Destroy();
}



