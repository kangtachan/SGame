// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SGTileBase.h"
#include "SGGlobalGameInstance.h"

#include "SGEnemyTileBase.generated.h"

/**
 * Enemy base tile
 */
UCLASS()
class SGAME_API ASGEnemyTileBase : public ASGTileBase
{
	GENERATED_BODY()

	friend class USGCheatManager;

public:
	ASGEnemyTileBase();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Begin play hit */
	UFUNCTION(BlueprintCallable, Category = Hit)
	void BeginPlayHit();

protected:
	// The sprite asset for attcking state
	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UPaperSprite* Sprite_Attacking;

	// The sprite asset for dead state
	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UPaperSprite* Sprite_Dead;

	// The attack text render component
	UPROPERTY(Category = Text, EditAnywhere, BlueprintReadOnly)
	UTextRenderComponent* Text_Attack;

	// The armor text render component
	UPROPERTY(Category = Text, EditAnywhere, BlueprintReadOnly)
	UTextRenderComponent* Text_Armor;

	// The hp text render component
	UPROPERTY(Category = Text, EditAnywhere, BlueprintReadOnly)
	UTextRenderComponent* Text_HP;

	/** Begin attack */
	UFUNCTION(BlueprintCallable, Category = Attack)
	void EnemyAttack();

	// Start Attack, using BP function to implement, since it is more convenient to polish
	UFUNCTION(BlueprintImplementableEvent)
	void StartAttackAnimation();

	/** End attack */
	UFUNCTION(BlueprintCallable, Category = Attack)
	void ResetTile();

	// Start Attack, using BP function to implement, since it is more convenient to polish
	UFUNCTION(BlueprintImplementableEvent)
	void StartPlayHitAnimation();

private:
	// Holds the messaging endpoint.
	// Noted that this class may have two message endpoint, 
	// one for its parent messages and handlers, and 
	// one for itself
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;

	/** Handle begin attack message */
	void HandleBeginAttack(const FMessage_Gameplay_EnemyBeginAttack& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);

	/** Handle play hit animation and effects */
	void HandlePlayHit(const FMessage_Gameplay_EnemyGetHit& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);
};
