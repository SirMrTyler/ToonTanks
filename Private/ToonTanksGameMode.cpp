// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Sound/SoundBase.h"

void AToonTanksGameMode::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

// This handles which actor died, and what happens when they die.
void AToonTanksGameMode::ActorDied(AActor* DeadActor) 
{
    if(DeadActor == Tank) {
        Tank->HandleDestruction();
        
        if(ToonTanksPlayerController) 
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        UGameplayStatics::PlaySound2D(this, YouLoseAudio);
        GameOver(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) 
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0) 
        {
            UGameplayStatics::PlaySound2D(this, YouWinAudio);
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::HandleGameStart() 
{
    // This defines how many towers need to be destroy for the user to win
    TargetTowers = GetTargetTowerCount();
    // This sets the controller of the tank to the first input on user system
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // This declares which tank the player will control
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController) 
    {
        // This is what disallows the player to move during the countdown at the beginning of the game.
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false);
    }
}

// This tells us how many Towers are left.
int32 AToonTanksGameMode::GetTargetTowerCount() 
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();    
}
