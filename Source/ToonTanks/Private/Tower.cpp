// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
	FireRange = 1000;
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation(), RotationSpeed);
	}
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (IsInFireRange())
	{
		Fire();
	}
}

bool ATower::IsInFireRange()
{
	if (Tank && !Tank->IsHidden())
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange ? true : false;
	}
	return false;
}
