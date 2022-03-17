// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HMPhrike_Orb.generated.h"

UCLASS()
class HMPHRIKE_API AHMPhrike_Orb : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHMPhrike_Orb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitOrb(float Speed, float TimeToLaunch);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Custom")
		UStaticMeshComponent* OrbMesh;
	UPROPERTY(EditAnywhere, Category = "Custom")
		UParticleSystem* OnHitExplosion = nullptr;
	UPROPERTY(EditAnywhere, Category = "Custom")
		class UParticleSystemComponent* FireTraceParticles = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* OrbMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MovementSpeed = 1300.f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float DamageToApply = 15.f;

	float LaunchTime;
	float InitialSpeed;

	UFUNCTION()
	void LaunchOrb();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
