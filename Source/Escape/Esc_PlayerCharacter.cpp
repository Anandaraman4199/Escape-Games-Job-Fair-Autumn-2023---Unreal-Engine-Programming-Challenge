// Fill out your copyright notice in the Description page of Project Settings.


#include "Esc_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraActor.h"
#include "Esc_Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Esc_EnemyCharacter.h"

// Sets default values
AEsc_PlayerCharacter::AEsc_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	RotationDirection = 0;
	RotationRate = 125;

	GunHolderComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunHolder"));
	GunHolderComponent->SetupAttachment(GetMesh(), TEXT("GunSocket"));

	RotationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RotationWidget"));
	RotationWidget->SetupAttachment(GetMesh());

	DesiredRotationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DesiredRotationWidget"));
	DesiredRotationWidget->SetupAttachment(GetMesh());

	RotationWidget->SetRelativeRotation(FRotator(90, -90, 0));
	DesiredRotationWidget->SetRelativeRotation(FRotator(90, -90, 0));


	Health = 100;
	MaxHealth = 100;

}

// Called when the game starts or when spawned
void AEsc_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	FollowCamera = (GetWorld()->SpawnActor<ACameraActor>(FVector(0, 0, 0), FRotator(-45, -45, 0), FActorSpawnParameters()));
	GetController()->CastToPlayerController()->SetViewTarget((AActor*)FollowCamera, FViewTargetTransitionParams());

	GetController()->CastToPlayerController()->bShowMouseCursor = true;

	if (GunHolderComponent->GetChildActor()) {
		(Cast<AEsc_Gun>(GunHolderComponent->GetChildActor()))->OwnerPlayer = this;
	}

}

// Called every frame
void AEsc_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement();

	if (bAiming)
		UpdateRotation(DeltaTime);
	else {
		DesiredRotationWidget->SetRelativeLocation(FVector(0, 0, 2));
		DesiredRotationWidget->SetRelativeRotation(FRotator(90, -90, 0));
		bRotating = false;
	}
		

	UpdateCamera();

}

// Called to bind functionality to input
void AEsc_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AEsc_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AEsc_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AEsc_PlayerCharacter::AimPressed);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AEsc_PlayerCharacter::AimReleased);
	PlayerInputComponent->BindAction(TEXT("Kill"), EInputEvent::IE_Pressed, this, &AEsc_PlayerCharacter::InstantKill);
	PlayerInputComponent->BindAction(TEXT("MainMenu"), EInputEvent::IE_Pressed, this, &AEsc_PlayerCharacter::MainMenu);
	PlayerInputComponent->BindAction(TEXT("NoReload"), EInputEvent::IE_Pressed, this, &AEsc_PlayerCharacter::NoReloadTime);
}

// Called when the MoveForward input pressed
void AEsc_PlayerCharacter::MoveForward(float axis)
{

	if (FollowCamera) {
		FwdMovementVec = FollowCamera->GetActorForwardVector();
		FwdMovementVec = FwdMovementVec * axis;
		FwdMovementVec.Z = 0;
	}

}

// Called when the MoveRight input pressed
void AEsc_PlayerCharacter::MoveRight(float axis)
{

	if (FollowCamera) {
		RgtMovementVec = FollowCamera->GetActorRightVector();
		RgtMovementVec = RgtMovementVec * axis;
		RgtMovementVec.Z = 0;
	}

}

// Called when the Aim input pressed
void AEsc_PlayerCharacter::AimPressed()
{	

	bAiming = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	
}

// Called when the Aim input released
void AEsc_PlayerCharacter::AimReleased()
{

	bAiming = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called every frame to update the player movement
void AEsc_PlayerCharacter::UpdateMovement()
{

	FVector MovementVec = FwdMovementVec + RgtMovementVec;
	MovementVec.Normalize(0.001f);
	AddMovementInput(MovementVec, 1);

}

void AEsc_PlayerCharacter::UpdateRotation(float DeltaTime) {

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

	float mouseX = 0, mouseY = 0;
	GetController()->CastToPlayerController()->GetMousePosition(mouseX, mouseY);

	mouseX = mouseX - ViewportCenter.X;
	mouseY = mouseY - ViewportCenter.Y;

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0, 0, 0), FVector(mouseX, mouseY, 0));

	DesiredRotation = GetActorRotation();

	FRotator currentRotation = GetActorRotation();

	DesiredRotation.Yaw = rotation.Yaw + 45;

	if (DesiredRotation.Yaw > 180)
		DesiredRotation.Yaw = DesiredRotation.Yaw - 360;

	RotationDirection = DesiredRotation.Yaw - currentRotation.Yaw;

	if (abs(RotationDirection) > 180)
		RotationDirection = -RotationDirection;

	RotationDirection = (RotationDirection / abs(RotationDirection));

	FRotator NewWidgetRotation = DesiredRotation;

	NewWidgetRotation.Roll += 180;
	NewWidgetRotation.Pitch += 90;
	
	DesiredRotationWidget->SetWorldRotation(NewWidgetRotation);
	DesiredRotationWidget->SetRelativeLocation(FVector(0,0,20));

	if (abs(currentRotation.Yaw - DesiredRotation.Yaw) > 1)
	{
		bRotating = true;
		currentRotation.Yaw = currentRotation.Yaw + RotationDirection * RotationRate * DeltaTime;
		SetActorRotation(currentRotation);
	}
	else
		bRotating = false;
}

FVector AEsc_PlayerCharacter::GetLeftHandIKLocation()
{
	
	FVector HandIK(0, 0, 0);

	if (GunHolderComponent->GetChildActor()) {

		HandIK = GunHolderComponent->GetChildActor()->GetRootComponent()->GetSocketLocation(TEXT("LeftHandIK"));
	}
	
	return HandIK;
}

void AEsc_PlayerCharacter::InstantKill()
{
	if (XP > 600) {

		TArray<AActor*> OutEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEsc_EnemyCharacter::StaticClass(), OutEnemies);
		for (auto i : OutEnemies) {
			Cast<AEsc_EnemyCharacter>(i)->InstantKill();
		}

		XP -= 600;
	}
}


bool AEsc_PlayerCharacter::isShooting()
{
	if (GunHolderComponent)
	{
		if(GunHolderComponent->GetChildActor())
			return (Cast<AEsc_Gun>(GunHolderComponent->GetChildActor()))->bFiring;
	}
		
		return false;
}

bool AEsc_PlayerCharacter::isReloading()
{
	if (GunHolderComponent)
	{
		if (GunHolderComponent->GetChildActor())
			return (Cast<AEsc_Gun>(GunHolderComponent->GetChildActor()))->bReloading;
	}

	return false;
}

void AEsc_PlayerCharacter::MainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu_Map");
}

void AEsc_PlayerCharacter::PickUp(int inXP, int inHealth)
{
	this->XP += inXP;
	this->Health += inHealth;
	if (this->Health > 100)
		this->Health = 100;
}

// Called every frame at the end of Tick to Update Camera Position
void AEsc_PlayerCharacter::UpdateCamera()
{	

	FVector NewLocation = GetActorLocation() + FVector(-CameraToPlayerDistance, 
		CameraToPlayerDistance, 
		CameraToPlayerDistance + (CameraToPlayerDistance / 4));

	FollowCamera->SetActorLocation(NewLocation);

}

float AEsc_PlayerCharacter::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0) {
		bDeath = true;
		
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu_Map");
	}
		
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEsc_PlayerCharacter::NoReloadTime()
{
	if (XP > 500) {

		Cast<AEsc_Gun>(GunHolderComponent->GetChildActor())->ReloadTime = 0.1f;
		
		FTimerHandle ReloadResetHandle;

		GetWorld()->GetTimerManager().SetTimer(ReloadResetHandle, this, &AEsc_PlayerCharacter::ReloadTimeReset, 15, false);
		XP -= 500;
	}
	
}

void AEsc_PlayerCharacter::ReloadTimeReset()
{
	Cast<AEsc_Gun>(GunHolderComponent->GetChildActor())->ReloadTime = 4;
}
