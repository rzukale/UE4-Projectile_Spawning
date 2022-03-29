// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMPhrike_OrbSpawnerBase.h"
#include "HMPhrike_OrbSpawnerHand.generated.h"

/**
 * 
 */
UCLASS()
class HMPHRIKE_API AHMPhrike_OrbSpawnerHand : public AHMPhrike_OrbSpawnerBase
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
	void CheckAccuracy();
	bool OrbTargetTrace(FHitResult& Hit);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float OrbSpawnInterval = 0.2f;
	float LastOrbSpawnTime = 0.f;
	float MaxRange = 20000.f;
};
