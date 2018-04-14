// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CheatManager.h"
#include "MessageEndpoint.h"
#include "SGameMessages.h"
#include "SGCheatManager.generated.h"

/** 
 * Some test and cheat function here
 */
UCLASS(Within = SGPlayerController)
class SGAME_API USGCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	USGCheatManager();

	// Player finish builld the link line
	UFUNCTION(exec)
	void BeginAttack();
	
	UFUNCTION(exec)
	void UseSkill(int32 inSkillIndex);

	// Manually Start the game
	UFUNCTION(exec)
	void StartGame();

	// Manually Start the new round
	UFUNCTION(exec)
	void NewRound();

	// Force collect the link line
	UFUNCTION(exec)
	void ForceCollect();

	// Player finish builld the link line
	UFUNCTION(exec)
	void PlayerEndBuildPath();

	//Test Set Health
	UFUNCTION(exec)
	void SetHealth(int newHealth);

	//Test Reset gird
	UFUNCTION(exec)
	void ResetGrid();

private:

	// Holds the messaging endpoint.
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;
};
