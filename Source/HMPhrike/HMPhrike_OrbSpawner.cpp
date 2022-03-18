// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_OrbSpawner.h"
#include "Components/BoxComponent.h"
#include "HMPhrike_Orb.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHMPhrike_OrbSpawner::AHMPhrike_OrbSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if (Root != nullptr)
	{
		SetRootComponent(Root);
	}
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	if (SpawnVolume != nullptr && Root != nullptr)
	{
		SpawnVolume->SetupAttachment(Root);
	}
}

// Called when the game starts or when spawned
void AHMPhrike_OrbSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHMPhrike_OrbSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TotalOrbsToSpawn > 0)
	{
		SpawnOrb();
	}
}


// DEPRECATED
void AHMPhrike_OrbSpawner::SpawnOrbs()
{
	Speed = OrbInitialSpeed;
	OrbRotation = FRotator::ZeroRotator;
	OrbRotation.Pitch = InitialPitchAngle;
	for (int32 i = 0; i < OrbSpawnCycles; i++)
	{
		for (int32 j = 0; j < OrbsPerCycle; j++)
		{
			OrbRotation.Yaw += YawIncreaseBetweenOrbs;
			FTransform Transform(OrbRotation, GetActorLocation());
			AHMPhrike_Orb* Orb = GetWorld()->SpawnActorDeferred<AHMPhrike_Orb>(OrbClass, Transform);
			Orb->InitOrb(Speed, TimeDelayBetweenSpawnAndLaunch);
			UGameplayStatics::FinishSpawningActor(Orb, Transform);
		}
		OrbRotation.Pitch += PitchIncreaseBetweenOrbCycles;
		Speed += OrbSpeedIncrease;
	}
}

void AHMPhrike_OrbSpawner::CallOrbSpawn()
{
	TotalOrbsToSpawn = OrbsPerCycle * OrbSpawnCycles;
	OrbRotation = FRotator::ZeroRotator;
	OrbRotation.Pitch = InitialPitchAngle;
	Speed = OrbInitialSpeed;
}

void AHMPhrike_OrbSpawner::SpawnOrb()
{
	OrbRotation.Yaw += YawIncreaseBetweenOrbs;
	FTransform Transform(OrbRotation, GetActorLocation());
	if (OrbClass != nullptr)
	{
		AHMPhrike_Orb* Orb = GetWorld()->SpawnActorDeferred<AHMPhrike_Orb>(OrbClass, Transform);
		if (Orb != nullptr)
		{
			Orb->InitOrb(Speed, TimeDelayBetweenSpawnAndLaunch);
		}
		UGameplayStatics::FinishSpawningActor(Orb, Transform);
	}
	TotalOrbsToSpawn--;
	if (TotalOrbsToSpawn % OrbsPerCycle == 0)
	{
		OrbRotation.Pitch += PitchIncreaseBetweenOrbCycles;
		Speed += OrbSpeedIncrease;
	}
}

