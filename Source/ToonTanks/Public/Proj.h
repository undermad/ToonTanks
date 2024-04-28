// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proj.generated.h"

class UProjectileMovementComponent;
class USoundBase;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API AProj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category="Component")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category="Component")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	UParticleSystemComponent* SmokeTrail;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
};
