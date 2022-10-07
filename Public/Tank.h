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
	
	// Allows enabling of keybinds for the user that are determined within unreal's editor
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// This will be called anytime an actor needs to be destoryed/killed
	void HandleDestruction();
	
	// This is a getter function usable on other classes to return the playercontroller of the tank
	APlayerController* GetTankController() const {return TankPlayerController;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Allows a camera to be added to the viewport
	UPROPERTY(VisibleAnywhere, Category = "Camera Components") 
	class UCameraComponent* TankCamera;
	
	// Adds an adjustable vector to tie the camera to the tank
	UPROPERTY(VisibleAnywhere, Category = "Camera Components")
	class USpringArmComponent* TankSpringArm;
	
	// Base movement speed varialbe for the tank
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 400.0f;
	
	// Will be used to adjust the rotational speed of the tanks turret
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 100.0f;
	
	// Function used to handle move logic when key is pressed
	void Move(float value);
	
	// Function used to handle rotation when key is pressed
	void Turn(float value);

	APlayerController* TankPlayerController;
};
