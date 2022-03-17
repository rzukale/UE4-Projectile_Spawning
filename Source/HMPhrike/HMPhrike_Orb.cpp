// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_Orb.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HMPhrikeCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"

// Sets default values
AHMPhrike_Orb::AHMPhrike_Orb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Orb Mesh"));
	RootComponent = OrbMesh;
	OrbMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Orb Movement Component"));
	FireTraceParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Orb Fire trail"));
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

// Called every frame
void AHMPhrike_Orb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHMPhrike_Orb::InitOrb(float Speed , float TimeToLaunch)
{
	InitialSpeed = Speed;
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AHMPhrike_Orb::LaunchOrb, TimeToLaunch, false);
}

void AHMPhrike_Orb::LaunchOrb()
{
	if (OrbMovementComponent != nullptr)
	{
		OrbMovementComponent->MaxSpeed = InitialSpeed;
		OrbMovementComponent->InitialSpeed = InitialSpeed;
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
