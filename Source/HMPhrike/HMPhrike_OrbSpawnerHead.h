// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMPhrike_OrbSpawnerBase.h"
#include "HMPhrike_OrbSpawnerHead.generated.h"

/**
 * 
 */
UCLASS()
class HMPHRIKE_API AHMPhrike_OrbSpawnerHead : public AHMPhrike_OrbSpawnerBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SpawnOrbs() override;
	virtual void SpawnOrb(const float& OrbSpeed) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InitOrbSpawning() override;

private:

	void LaunchOrbs();

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float OrbRotationIncrement = 10.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float InitialPitchAngle = -40.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float OrbSpeedIncrease = 125.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float YawIncreaseBetweenOrbs = 15.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float PitchIncreaseBetweenOrbCycles = 10.f;
	UPROPERTY()
	TArray<AHMPhrike_Orb*> OrbArray;

	float Speed;
	bool bLaunchingOrbs = false;
};
