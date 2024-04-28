// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UParticleEmitter;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void HandleDestruction();

protected:
	void RotateTurret(FVector Target, float RotationSpeed);
	void Fire();
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess))
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess))
	USceneComponent* ProjectileSpawnComponent;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProj> ProjClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* DeathSound;


	
};
