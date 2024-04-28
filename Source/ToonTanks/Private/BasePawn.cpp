// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Proj.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Capsule);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawner"));
	ProjectileSpawnComponent->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// Todo: Visual/sound
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

}

void ABasePawn::RotateTurret(FVector Target, float RotationSpeed)
{
	FVector ToTarget = Target - TurretMesh->GetComponentLocation();
	FRotator Rotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			Rotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			RotationSpeed
		));
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnComponent->GetComponentLocation();
	FRotator Rotation = TurretMesh->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProj>(ProjClass, Location, Rotation);
	Projectile->SetOwner(this);
}
