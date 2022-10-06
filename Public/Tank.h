// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void HandleDestruction();
	APlayerController* GetTankController() const {return TankPlayerController;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera Components") 
	class UCameraComponent* TankCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera Components")
	class USpringArmComponent* TankSpringArm;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 100.0f;

	void Move(float value);
	void Turn(float value);

	APlayerController* TankPlayerController;
};
