// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()


public:
	ATower();
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void HandleDestruction();


private:

	ATank* Tank;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Behavior")
	float FireRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Behavior")
	float RotationSpeed;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool IsInFireRange();

	
};
