// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_Orb.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HMPhrikeCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AHMPhrike_Orb::AHMPhrike_Orb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Orb Mesh"));
	if (!ensure(OrbMesh != nullptr)) return;
	RootComponent = OrbMesh;
	OrbMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Orb Movement Component"));
	if (!ensure(OrbMovementComponent != nullptr)) return;
	FireTraceParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Orb Fire trail"));
	if (!ensure(FireTraceParticles != nullptr)) return;
	FireTraceParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHMPhrike_Orb::BeginPlay()
{
	Super::BeginPlay();

	if (OrbMesh != nullptr)
	{
		OrbMesh->OnComponentHit.AddDynamic(this, &AHMPhrike_Orb::OnHit);
	}
}

void AHMPhrike_Orb::InitOrb(const float& Speed)
{
	if (OrbMovementComponent != nullptr)
	{
		OrbMovementComponent->MaxSpeed = Speed;
		OrbMovementComponent->InitialSpeed = Speed;
		OrbMovementComponent->Velocity = FVector::ZeroVector;
	}
}

void AHMPhrike_Orb::SetInvisible()
{
	if (OrbMesh != nullptr && FireTraceParticles != nullptr)
	{
		OrbMesh->SetVisibility(false);
		FireTraceParticles->SetVisibility(false);
		bIsVisible = false;
	}
}

void AHMPhrike_Orb::LaunchOrb()
{
	if (OrbMovementComponent != nullptr)
	{
		if (bIsVisible == false && OrbMesh != nullptr && FireTraceParticles != nullptr)
		{
			OrbMesh->SetVisibility(true);
			FireTraceParticles->SetVisibility(true);
			bIsVisible = true;
		}
		OrbMovementComponent->Velocity = GetActorRotation().Vector() * OrbMovementComponent->InitialSpeed;
	}
}

void AHMPhrike_Orb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OnHitExplosion != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, OnHitExplosion, GetActorLocation(), GetActorRotation());
	}
	if (OtherActor != nullptr)
	{
		AHMPhrikeCharacter* PlayerCharacter = Cast<AHMPhrikeCharacter>(OtherActor);
		if (PlayerCharacter != nullptr)
		{
			FDamageEvent DamageEvent;
			PlayerCharacter->TakeDamage(DamageToApply, DamageEvent, nullptr, this);
		}
	}
	Destroy();
}
