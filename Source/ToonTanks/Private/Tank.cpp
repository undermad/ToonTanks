// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "cmath"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	MaxVelocity = 8;
	SlowingVelocity = 7;
	Acceleration = 15;
	TurningSpeed = 150;
	IsMoving = false;
	CurrentVelocity = FVector::ZeroVector;
	RotationSpeed = 5;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PerformMove(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint, RotationSpeed);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	if (DeathCameraShake)
	{
		TankPlayerController->ClientStartCameraShake(DeathCameraShake);
	}
}

void ATank::Move(float Value)
{
	IsMoving = true;
	double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = (Value * Acceleration) * DeltaTime;
	if (!(abs(CurrentVelocity.X) >= MaxVelocity))
	{
		CurrentVelocity.X += DeltaLocation.X;
	}
	IsMoving = false;
}

void ATank::PerformMove(float DeltaTime)
{
	if (!IsMoving)
	{
		if (CurrentVelocity.X > 0)
		{
			CurrentVelocity.X = CurrentVelocity.X - (SlowingVelocity * DeltaTime);
		}
		else if (CurrentVelocity.X < 0)
		{
			CurrentVelocity.X = CurrentVelocity.X + (SlowingVelocity * DeltaTime);
		}
	}

	AddActorLocalOffset(CurrentVelocity, true);
}

void ATank::Turn(float Value)
{
	double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = (Value * TurningSpeed) * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}
