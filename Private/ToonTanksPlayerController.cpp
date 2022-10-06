// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled) {
    // This tells the system when the tank can be controlled by the user depending on whether bPlayerEnabled is true or not
    if(bPlayerEnabled) {
        GetPawn()->EnableInput(this);
    }
    else {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}
