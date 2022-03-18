// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_BossCharacter.h"
#include "HMPhrike_OrbSpawner.h"

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

	Spawner = GetWorld()->SpawnActor<AHMPhrike_OrbSpawner>(SpawnerClass);
	if (!ensure(Spawner != nullptr)) return;
	if (Spawner != nullptr)
	{
		Spawner->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform,
			TEXT("OrbSpawnerHead"));
		Spawner->SetOwner(this);
	}
}

// Called every frame
void AHMPhrike_BossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHMPhrike_BossCharacter::LaunchOrbs()
{
	if (Spawner != nullptr)
	{
		Spawner->CallOrbSpawn();
		//Spawner->SpawnOrbs();
	}
}
