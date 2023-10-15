// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_PickUp.h"
#include "Esc_PickUp_DataAsset.h"
#include "Components/StaticMeshComponent.h"
#include "Esc_PlayerCharacter.h"

// Sets default values
AEsc_PickUp::AEsc_PickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetupAttachment(RootComponent);

	MeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AEsc_PickUp::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AEsc_PickUp::OnPlayerBeginOverlap);

	if (DataAsset) {
		Name = DataAsset->Name;
		MeshComp->SetStaticMesh(DataAsset->Mesh);
		Xp = DataAsset->Xp;
		Health = DataAsset->Health;
	}
	

	
}

// Called every frame
void AEsc_PickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0, 180 * DeltaTime, 0));

}

void AEsc_PickUp::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEsc_PlayerCharacter>(OtherActor)) {
		Cast<AEsc_PlayerCharacter>(OtherActor)->PickUp(Xp, Health);
		Destroy();
	}
	
}

