// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;
    
	// Here we create/declare a movable arm for the camera as the parent component.
	TankSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
	TankSpringArm->SetupAttachment(RootComponent);

	// This creates/attaches a camera to our root component
	TankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	TankCamera->SetupAttachment(TankSpringArm);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// This if statement handles the cursors location within the viewport to update the turrets rotation every frame.
	if(TankPlayerController) {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
}

// This function destroys, hides, and stops the actor from being able to tick. It's called during death.
void ATank::HandleDestruction() {

    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    	TankPlayerController = Cast<APlayerController>(GetController());
}

// This function creates input commands usable to the user/controller
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float value) 
{
	// This fector defines the tanks current location
    	FVector DeltaTankLocation(0.f);
    
	// We define the tanks X axis location so that the tank is always facing forward while it moves.
    	DeltaTankLocation.X = value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;

	// This moves the tank on it's x axis according to value (0 if user isn't pressing move, 1 if they are), current location, and speed.
    	AddActorLocalOffset(DeltaTankLocation, true);
}

void ATank::Turn(float value) 
{
	// This states the current rotation of the tanks turret mesh
    	FRotator DeltaTankRotation(0.f);
	// We rotate by Yaw (or z axis) so that the turret only rotates in a normal way.
    	DeltaTankRotation.Yaw = value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	
	// This rotates the tank as long as value isn't 0 (when the user is pressing the turn keys). The speed it turns is based off TurnRate variable).
    	AddActorLocalRotation(DeltaTankRotation, true);
}
