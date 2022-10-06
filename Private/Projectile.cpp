// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// This allows the actor the ability to be updated every frame when set to true.
	PrimaryActorTick.bCanEverTick = true;

	// Here we set our Projectile's static mesh as the parent component of the actor
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	// Here we create the object and give it default speed values
	ProjectileMoverComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Mover"));
	ProjectileMoverComp->MaxSpeed = 1500.f;
	ProjectileMoverComp->InitialSpeed = 1500.f;

	// This section attaches particle effects to our ProjectileComponent
	ParticleSysComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	ParticleSysComponent->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	// Pretty straight forward, this plays a sound at the location of the projectiles actor where it collides with something.
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	// This allows us to make sure the projectile fired by the user doesn't hit that same user.
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) {
		Destroy();
		return;
	}
	
	// This returns the controller (user) of the person who initiated that projectile launch.
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	
	// This states that if the actor hit by missle isn't the person who launched the projectile then damage will be dealt to that actor.
	if(OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}
		if(HitCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		
	}
	Destroy();
	
}

