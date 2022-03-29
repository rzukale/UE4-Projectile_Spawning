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
	void SpawnOrbsHands();

protected:
	virtual void BeginPlay() override;

};