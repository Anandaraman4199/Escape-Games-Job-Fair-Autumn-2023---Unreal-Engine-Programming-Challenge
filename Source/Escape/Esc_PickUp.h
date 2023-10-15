// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Esc_PickUp.generated.h"

UCLASS()
class ESCAPE_API AEsc_PickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEsc_PickUp();

	UPROPERTY(EditAnywhere)
	class UEsc_PickUp_DataAsset* DataAsset = nullptr;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp = nullptr;

	int Xp = 0;
	float Health = 0;

	FString Name ="";
		 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
