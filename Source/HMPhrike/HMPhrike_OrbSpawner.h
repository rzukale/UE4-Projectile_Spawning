// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HMPhrike_OrbSpawner.generated.h"

UCLASS()
class HMPHRIKE_API AHMPhrike_OrbSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHMPhrike_OrbSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* SpawnVolume = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnOrbs();
	void CallOrbSpawn();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	TSubclassOf<class AHMPhrike_Orb> OrbClass;

;	UPROPERTY(EditAnywhere, Category = "Combat")
	float OrbRotationIncrement = 10.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	int32 OrbSpawnCycles = 4;
	UPROPERTY(EditAnywhere, Category = "Combat")
	int32 OrbsPerCycle = 24;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float InitialPitchAngle = -40.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float OrbSpeedIncrease = 125.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float OrbInitialSpeed = 260.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float YawIncreaseBetweenOrbs = 15.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float PitchIncreaseBetweenOrbCycles = 10.f; \
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TimeDelayBetweenSpawnAndLaunch = 0.5f;

	uint32 TotalOrbsToSpawn = 0;
	float Speed;
	FRotator OrbRotation;

	void SpawnOrb();

};
