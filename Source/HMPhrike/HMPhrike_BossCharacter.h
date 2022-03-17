// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HMPhrike_BossCharacter.generated.h"

class AHMPhrike_OrbSpawner;

UCLASS()
class HMPHRIKE_API AHMPhrike_BossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHMPhrike_BossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchOrbs();

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHMPhrike_OrbSpawner> SpawnerClass;
	UPROPERTY()
	AHMPhrike_OrbSpawner* Spawner = nullptr;
};
