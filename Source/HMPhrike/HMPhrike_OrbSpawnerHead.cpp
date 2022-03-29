// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_OrbSpawnerHead.h"
#include "HMPhrike_Orb.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"

void AHMPhrike_OrbSpawnerHead::BeginPlay()
{
	Super::BeginPlay();

	int32 ArraySize = OrbSpawnCycles * OrbsPerCycle;
	check(ArraySize > 0);
	OrbArray.Reserve(ArraySize);
}

// Called every frame
// Check launching orbs boolean before spawning orbs so we make sure to launch orbs after the last orb has spawned
// and we do not do it in the same tick as last orb spawning

void AHMPhrike_OrbSpawnerHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLaunchingOrbs == true)
	{
		LaunchOrbs();
	}
	if (TotalOrbsToSpawn > 0)
	{
		SpawnOrbs();
	}
}

void AHMPhrike_OrbSpawnerHead::InitOrbSpawning()
{
	Super::InitOrbSpawning();

	if (OrbArray.Num() == 0)
	{
		TotalOrbsToSpawn = OrbsPerCycle * OrbSpawnCycles;
		OrbRotation = FRotator::ZeroRotator;
		OrbRotation.Pitch = InitialPitchAngle;
		Speed = OrbInitialSpeed;
	}
}

void AHMPhrike_OrbSpawnerHead::SpawnOrb(const float& OrbSpeed)
{
	Super::SpawnOrb(OrbSpeed);

	FTransform Transform(OrbRotation, GetActorLocation());
	if (OrbClass != nullptr)
	{
		AHMPhrike_Orb* Orb = GetWorld()->SpawnActorDeferred<AHMPhrike_Orb>(OrbClass, Transform);
		if (Orb != nullptr)
		{
			Orb->SetInvisible();
			Orb->InitOrb(OrbSpeed);
			OrbArray.Emplace(Orb);
		}
		UGameplayStatics::FinishSpawningActor(Orb, Transform);
	}
	if (OrbArray.Num() == OrbArray.Max())
	{
		bLaunchingOrbs = true;
	}
}

void AHMPhrike_OrbSpawnerHead::LaunchOrbs()
{
	for (AHMPhrike_Orb* const& Orb : OrbArray)
	{
		Orb->LaunchOrb();
	}
	OrbArray.Reset(OrbSpawnCycles * OrbsPerCycle);
	bLaunchingOrbs = false;
}

void AHMPhrike_OrbSpawnerHead::SpawnOrbs()
{
	Super::SpawnOrbs();

	OrbRotation.Yaw += YawIncreaseBetweenOrbs;
	SpawnOrb(Speed);
	TotalOrbsToSpawn--;
	if (TotalOrbsToSpawn % OrbsPerCycle == 0)
	{
		OrbRotation.Pitch += PitchIncreaseBetweenOrbCycles;
		Speed += OrbSpeedIncrease;
	}
}
