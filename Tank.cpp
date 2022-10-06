// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank() {
    PrimaryActorTick.bCanEverTick = true;
    
    TankSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
    TankSpringArm->SetupAttachment(RootComponent);

    TankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    TankCamera->SetupAttachment(TankSpringArm);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankPlayerController) {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
}

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

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float value) {

    FVector DeltaTankLocation(0.f);
    
    DeltaTankLocation.X = value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;

    AddActorLocalOffset(DeltaTankLocation, true);
}

void ATank::Turn(float value) {

    FRotator DeltaTankRotation(0.f);

    DeltaTankRotation.Yaw = value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
    AddActorLocalRotation(DeltaTankRotation, true);
}