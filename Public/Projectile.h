// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Will be used to show textures, and assests on the projectile
	UPROPERTY(VisibleAnywhere, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ProjectileMesh;
	
	// Will be used to handle movement/behavior of projectile
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UProjectileMovementComponent* ProjectileMoverComp;

	// Will handle what happens with the projectile hits something while moving.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Can be sit within code/editor. Used to specifiy how much damage the projectile does to other actors.
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 50.f;

	// Will be used to create particles upon collision
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	// Used to handle the smoke trail following the projectile.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* ParticleSysComponent;

	// Will let us allocate a sound effect asset when turret is fired.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	// Allows defenition of sound asset when collision occurs.
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* ImpactSound;

	// Upon collision this will allow a camerashake effect to happen on the viewport
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
