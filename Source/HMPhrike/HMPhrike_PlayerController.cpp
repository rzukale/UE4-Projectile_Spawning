// Fill out your copyright notice in the Description page of Project Settings.


#include "HMPhrike_PlayerController.h"
#include "Blueprint/UserWidget.h"

void AHMPhrike_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}
