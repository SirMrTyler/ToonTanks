// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Creates a CapsuleComp object that we can add onto other objects within the game
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	// Setting RootComponent equal to our CapsuleComp makes it the parent component on it's object (in this case it's the BasePawn)
	RootComponent = CapsuleComp;
	
	// Here we're attaching a meshcomponent to our RootComponent so that we can add textures to it's mesh (Base Mesh will be used for tanks).
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	// Here we're attaching a meshcomponent to our basemesh that can be used to add textures to our Tanks Turrets.
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// Here we're creating/attaching the mesh projectile to our turretmesh that will be used to fire missles.
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	BasePawnParticleSysComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Death Particles"));
}

// This function gets called whenever a BasePawn's health is <= 0
void ABasePawn::HandleDestruction() {
	if(DeathParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
		
}

// This function gets called with the user moves their mouse around and is used to rotate the turret mesh on top of base mesh.
void ABasePawn::RotateTurret(FVector LookAtTarget) {
	// LookAtTarget is the locational vector of the mouse cursor.
	// Here we take the LookAtTarget and subtract from the turrets current location to get how far the turret must move.
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	
	// This creates a local rotational variable that rotates the turret according to ToTarget
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	
	// Using the local rotation variable we made we set the turrets rotational data to it so that the user sees rotation of the mesh
	TurretMesh->SetWorldRotation(
		FMath::RInterpConstantTo(TurretMesh->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		300.f));
}

// This function gets called when the user press the LMB. It handles the projectiles creation/location/rotation/ownership.
void ABasePawn::Fire() {

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

}



