// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_OrbSpawnerHand.h"
#include "HMPhrikeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HMPhrike_Orb.h"

void AHMPhrike_OrbSpawnerHand::BeginPlay()
{
	Super::BeginPlay();
}

void AHMPhrike_OrbSpawnerHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TotalOrbsToSpawn > 0)
	{
		if (GetWorld()->GetTimeSeconds() > (LastOrbSpawnTime + OrbSpawnInterval))
		{
			CheckAccuracy();
			SpawnOrbs();
		}
	}
}

void AHMPhrike_OrbSpawnerHand::InitOrbSpawning()
{
	Super::InitOrbSpawning();

	AHMPhrikeCharacter* PlayerCharacter = Cast<AHMPhrikeCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerCharacter != nullptr)
	{
		FVector FireDirection = PlayerCharacter->GetActorLocation() - GetActorLocation();
		OrbRotation = FRotator(FireDirection.Rotation().Pitch, FireDirection.Rotation().Yaw, 0.f);
		TotalOrbsToSpawn = OrbSpawnCycles * OrbsPerCycle;
	}
}

void AHMPhrike_OrbSpawnerHand::CheckAccuracy()
{
	FHitResult Hit;
	OrbTargetTrace(Hit);
	AHMPhrikeCharacter* HitActor = Cast<AHMPhrikeCharacter>(Hit.GetActor());
	if (HitActor == nullptr) // our trace has missed the player, therefore we have to reassign firing direction towards players new position
	{
		AHMPhrikeCharacter* PlayerCharacter = Cast<AHMPhrikeCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (PlayerCharacter != nullptr)
		{
			FVector NewTarget = PlayerCharacter->GetActorLocation() - GetActorLocation();
			OrbRotation = FRotator(NewTarget.Rotation().Pitch, NewTarget.Rotation().Yaw, 0.f);
		}
	}
}

/*
* Strictly speaking, Casting a ray here is unnecessary, as you can simply calculate the new target vector here
* and reduce overhead. This is simply to showcase a potential situation where you could do this.
*/
bool AHMPhrike_OrbSpawnerHand::OrbTargetTrace(FHitResult& Hit)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + OrbRotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AHMPhrike_OrbSpawnerHand::SpawnOrbs()
{
	Super::SpawnOrbs();

	SpawnOrb(OrbInitialSpeed);
	TotalOrbsToSpawn--;
	LastOrbSpawnTime = GetWorld()->GetTimeSeconds();
}

void AHMPhrike_OrbSpawnerHand::SpawnOrb(const float& OrbSpeed)
{
	Super::SpawnOrb(OrbSpeed);

	FTransform Transform(OrbRotation, GetActorLocation());
	if (OrbClass != nullptr)
	{
		AHMPhrike_Orb* Orb = GetWorld()->SpawnActorDeferred<AHMPhrike_Orb>(OrbClass, Transform);
		if (Orb != nullptr)
		{
			Orb->InitOrb(OrbSpeed);
		}
		UGameplayStatics::FinishSpawningActor(Orb, Transform);
		Orb->LaunchOrb();
	}
}
