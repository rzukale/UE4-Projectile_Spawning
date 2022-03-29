// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_OrbSpawnerBase.h"
#include "Components/BoxComponent.h"
#include "HMPhrikeCharacter.h"

// Sets default values
AHMPhrike_OrbSpawnerBase::AHMPhrike_OrbSpawnerBase()
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
void AHMPhrike_OrbSpawnerBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHMPhrike_OrbSpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHMPhrike_OrbSpawnerBase::SpawnOrb(const float& OrbSpeed)
{
}

void AHMPhrike_OrbSpawnerBase::InitOrbSpawning()
{
}

void AHMPhrike_OrbSpawnerBase::SpawnOrbs()
{
}

