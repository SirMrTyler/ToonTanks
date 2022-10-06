// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	// This will allows us to have an invisible sphere around the actor that can be used for collision, location, rotation, etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	// This will become the base of our tank
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	// This will become the turret that will sit on top of our tanks base mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh;

	// This declares where our projectile will spawn at. It will be attached to the turretmesh's location.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;

	// Here we forward declare a projectile class that will be used to handle all behavior of our projectile.
	UPROPERTY(EditDefaultsOnly, Category = "Combat");
	TSubclassOf<class AProjectile> ProjectileClass;

	// This will be a particle system that we define as our death particle asset.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	// This will be a component attached to our base pawn that handles it's turretmesh smoke particle asset when firing.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* BasePawnParticleSysComponent;

	// Will be define as our death explosion asset.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	// This handles the camerashake effect on the viewport when firing the turret.
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
