// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "HMPhrikeCharacter.h"
#include "HMPhrike_BossCharacter.h"

void AHMPhrike_AIController::SpawnOrbs()
{
	AHMPhrike_BossCharacter* BossCharacter = Cast<AHMPhrike_BossCharacter>(GetPawn());
	if (BossCharacter != nullptr)
	{
		BossCharacter->LaunchOrbs();
	}
}

void AHMPhrike_AIController::SpawnOrbsHands()
{
	AHMPhrike_BossCharacter* BossCharacter = Cast<AHMPhrike_BossCharacter>(GetPawn());
	if (BossCharacter != nullptr)
	{
		BossCharacter->LaunchOrbsHands();
	}
}

void AHMPhrike_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AHMPhrike_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AHMPhrikeCharacter* PlayerCharacter = Cast<AHMPhrikeCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerCharacter != nullptr)
	{
		APawn* AIPawn = GetPawn();
		if (AIPawn != nullptr)
		{
			FVector ToTarget = PlayerCharacter->GetActorLocation() - AIPawn->GetActorLocation();
			FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
			AIPawn->SetActorRotation(LookAtRotation);
		}
	}
}
