// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HMPhrike_AIController.generated.h"

/**
 * 
 */
UCLASS()
class HMPHRIKE_API AHMPhrike_AIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	void SpawnOrbs();

protected:
	virtual void BeginPlay() override;

private:
	class AHMPhrikeCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	TSubclassOf<class AHMPhrike_Orb> OrbClass;

	FVector OrbSpawnLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Custom")
	float OrbSpawnZValue = 1050.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
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
	float PitchIncreaseBetweenOrbCycles = 10.f;\
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TimeDelayBetweenSpawnAndLaunch = 0.5f;
};