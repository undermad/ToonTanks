// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UCameraShakeBase;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	virtual void HandleDestruction() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Components")
	UCameraComponent* CameraComponent;

	void Move(float Value);
	void PerformMove(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	float MaxVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	float SlowingVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	float Acceleration;

	FVector CurrentVelocity;

	bool IsMoving;

	void Turn(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	float TurningSpeed;

	APlayerController* TankPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;
};
