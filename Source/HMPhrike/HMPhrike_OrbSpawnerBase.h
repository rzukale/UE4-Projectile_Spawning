// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HMPhrike_OrbSpawnerBase.generated.h"

UCLASS()
class HMPHRIKE_API AHMPhrike_OrbSpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHMPhrike_OrbSpawnerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SpawnOrb(const float& OrbSpeed);
	virtual void SpawnOrbs();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InitOrbSpawning();

	// Base class variables
protected:
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* SpawnVolume = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	TSubclassOf<class AHMPhrike_Orb> OrbClass;
	UPROPERTY(EditAnywhere, Category = "Base Spawner Combat")
	int32 OrbSpawnCycles = 4;
	UPROPERTY(EditAnywhere, Category = "Base Spawner Combat")
	int32 OrbsPerCycle = 24;
	UPROPERTY(EditAnywhere, Category = "Base Spawner Combat")
	float OrbInitialSpeed = 260.f;

	FRotator OrbRotation;
	uint32 TotalOrbsToSpawn = 0;
};
