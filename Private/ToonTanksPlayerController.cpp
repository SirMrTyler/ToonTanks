// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

// This tells the system when the tank can be controlled by the user depending on whether bPlayerEnabled is true or not
void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled) {
    if(bPlayerEnabled) 
    {
        GetPawn()->EnableInput(this);
    }
    else 
    {
        GetPawn()->DisableInput(this);
    }
    
    // The cursor will only show up if the tank is allowed to be controlled by the user
    bShowMouseCursor = bPlayerEnabled;
}
