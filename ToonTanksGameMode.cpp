// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Sound/SoundBase.h"

void AToonTanksGameMode::BeginPlay() {
    Super::BeginPlay();

    HandleGameStart();
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor) {

    if(DeadActor == Tank) {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController) {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        UGameplayStatics::PlaySound2D(this, YouLoseAudio);
        GameOver(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) {

        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0) {
            UGameplayStatics::PlaySound2D(this, YouWinAudio);
            GameOver(true);
        }

    }

}

void AToonTanksGameMode::HandleGameStart() {
    
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController) {
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

int32 AToonTanksGameMode::GetTargetTowerCount() {

    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
    
}