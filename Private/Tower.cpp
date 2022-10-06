// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime) {

    Super::Tick(DeltaTime);

    if(InFireRange())
        RotateTurret(Tank->GetActorLocation());
    

}

void ATower::HandleDestruction() {

    Super::HandleDestruction();
    Destroy();

}

void ATower::BeginPlay() {

    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

}

void ATower::CheckFireCondition() {

if(InFireRange())
    Fire();
}

// This function declares whether or not there is something within the acceptable range for the turret to fire at. If there isn't, it won't fire.
bool ATower::InFireRange() 
{
    if(Tank) 
    {
        // Here we declare a local distance vector variable and called the Dist() function that subtracts the final distance from the start distance.
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        
        // As long as Distance is less than or equal to fire range, the towerturret is allowed to fire at the player.
        if(Distance <= FireRange)
            return true;
    }
    return false;
}
