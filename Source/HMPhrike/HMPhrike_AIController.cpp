// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HMPhrikeCharacter.h"
#include "HMPhrike_BossCharacter.h"
#include "HMPhrike_Orb.h"

void AHMPhrike_AIController::SpawnOrbs()
{
	APawn* AIPawn = GetPawn();
	TArray<AHMPhrike_Orb*> OrbPointers;
	if (AIPawn != nullptr)
	{
		float Speed = OrbInitialSpeed;
		FRotator OrbRotation = FRotator::ZeroRotator;
		OrbRotation.Pitch = InitialPitchAngle;
		for (int32 i = 0; i < OrbSpawnCycles; i++)
		{
			for (int32 j = 0; j < OrbsPerCycle; j++)
			{
				OrbRotation.Yaw += YawIncreaseBetweenOrbs;
				FTransform Transform(OrbRotation, OrbSpawnLocation);
				AHMPhrike_Orb* Orb = GetWorld()->SpawnActorDeferred<AHMPhrike_Orb>(OrbClass, Transform);
				Orb->InitOrb(Speed, TimeDelayBetweenSpawnAndLaunch);
				UGameplayStatics::FinishSpawningActor(Orb, Transform);
			}
			OrbRotation.Pitch += PitchIncreaseBetweenOrbCycles;
			Speed += OrbSpeedIncrease;
		}
	}
}

void AHMPhrike_AIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AHMPhrikeCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	APawn* AIPawn = GetPawn();
	if (AIPawn != nullptr)
	{
		OrbSpawnLocation = GetPawn()->GetActorLocation();
		OrbSpawnLocation.Z = OrbSpawnZValue;
	}
}

void AHMPhrike_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
