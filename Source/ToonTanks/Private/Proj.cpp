// Fill out your copyright notice in the Description page of Project Settings.


#include "Proj.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProj::AProj()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movment Component"));
	ProjectileMovementComponent->MaxSpeed = 10;
	ProjectileMovementComponent->InitialSpeed = 5;

	SmokeTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrail->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProj::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &AProj::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProj::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                  FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (Owner == nullptr || OtherActor == nullptr || OtherActor == this || OtherActor == Owner) return;

	auto MyInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, MyInstigator, MyOwner, DamageTypeClass);
	if (HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}

	if(HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}

	HitComponent->DestroyComponent();
}
