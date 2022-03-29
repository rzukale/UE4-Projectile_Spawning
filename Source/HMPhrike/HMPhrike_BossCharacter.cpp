// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_BossCharacter.h"
#include "HMPhrike_OrbSpawnerHand.h"
#include "HMPhrike_OrbSpawnerHead.h"

// Sets default values
AHMPhrike_BossCharacter::AHMPhrike_BossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHMPhrike_BossCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnerHead = GetWorld()->SpawnActor<AHMPhrike_OrbSpawnerHead>(SpawnerHeadClass);
	if (!ensure(SpawnerHead != nullptr)) return;
	if (SpawnerHead != nullptr)
	{
		SpawnerHead->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform,
			TEXT("OrbSpawnerHead"));
		SpawnerHead->SetOwner(this);
	}
	SpawnerLeftHand = GetWorld()->SpawnActor<AHMPhrike_OrbSpawnerHand>(SpawnerHandClass);
	if (!ensure(SpawnerLeftHand != nullptr)) return;
	if (SpawnerLeftHand != nullptr)
	{
		SpawnerLeftHand->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform,
			TEXT("OrbSpawnerLeftHand"));
		SpawnerLeftHand->SetOwner(this);
	}
}

// Called every frame
void AHMPhrike_BossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHMPhrike_BossCharacter::LaunchOrbs()
{
	if (SpawnerHead != nullptr)
	{
		SpawnerHead->InitOrbSpawning();
	}
}

void AHMPhrike_BossCharacter::LaunchOrbsHands()
{
	if (SpawnerLeftHand != nullptr)
	{
		SpawnerLeftHand->InitOrbSpawning();
	}
}
