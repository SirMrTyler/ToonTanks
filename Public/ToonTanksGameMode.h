// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Function tells us which actor died. Who would have thought?
	void ActorDied(AActor* DeadActor);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	// Used as a variable to delay the starting of the game while a countdown takes place.
	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* YouWinAudio;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* YouLoseAudio;
};
