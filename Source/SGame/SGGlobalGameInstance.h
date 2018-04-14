// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MessageEndpoint.h"
#include "MessageEndpointBuilder.h"
#include "SGameMessages.h"
#include "SGGlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SGAME_API USGGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USGGlobalGameInstance();

private:
	
	// Holds the messaging endpoint.
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;
};
