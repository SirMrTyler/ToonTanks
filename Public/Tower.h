// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when game starts
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	// Will be used as a comparison value between the tank and the tower telling the tower when it's allowed to shoot at the tank.
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 800.f;

	// Timer is used to declare add a delay between each shot the turret takes.
	FTimerHandle FireRateTimerHandle;
	
	// This is plugged into our timer as a conditional amount of time that must be waited for between each shot.
	float FireRate = 2.f;
	
	// Checks fire range, time between shots, and visibility of tank relative to the tower
	void CheckFireCondition();

	// Is tank in fire range = true; else = false
	bool InFireRange();
};
