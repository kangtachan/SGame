// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "MessageEndpoint.h"

#include "SGameMessages.h"
#include "SGTileBase.h"

#include "SGLinkLine.generated.h"

/** Link direction*/
UENUM()
enum class ELinkDirection : uint8
{
	ELD_Begin,
	ELD_Horizon,
	ELD_Vertical,
	ELD_BackSlash,
	ELD_Slash,
};

/** How to display the linkline */
UENUM()
enum class ELinkLineMode : uint8
{
	ELLM_Sprite,		// Use the 2D sprite linkline
	ELLM_Ribbon,		// Use the ribbon linkline
};

/** Linkline emitter contains a collision component to get tile overlap event */
UCLASS()
class SGAME_API ASGLinkLineEmitter : public AEmitter
{
	GENERATED_BODY()

public:
	ASGLinkLineEmitter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	* Linkline emitter hit the tile
	*/
	UFUNCTION()
	void OnLinkLineEmitterHitTile(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	/**
	* Linkline emitter overlap the tile
	*/
	UFUNCTION()
	void OnLinkLineEmitterOverlapTile(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UBoxComponent*				EmitterHeadCollision;
	UParticleSystemComponent*	EmitterPSC;
};

UCLASS()
class SGAME_API ASGLinkLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGLinkLine();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Update link line sprites*/
	UFUNCTION(BlueprintCallable, Category = Update)
	bool UpdateLinkLineDisplay();

	/** Update the link line*/
	UFUNCTION(BlueprintCallable, Category = Update)
	bool Update();

	// AActor interface
#if WITH_EDITOR
	virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;
#endif
	// End of AActor interface

	/** Return whether the current link line contains the tile*/
	UFUNCTION(BlueprintCallable, Category = Visitor)
	bool ContainsTileAddress(int32 inTileAddress);

	/** 
	 * Replay link animation 
	 *
	 * @return true to replay successfully
	 */
	UFUNCTION(BlueprintCallable, Category = Visitor)
	bool ReplayLinkAnimation(TArray<ASGTileBase*>& CollectTiles);

	/**
	* Replay link animation
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void BeginReplayLinkAnimation();

	/** End replay linkline animation */
	UFUNCTION(BlueprintCallable, Category = Visitor)
	void EndReplayLinkAnimation();

	/** 
	 * Replay linkline head ribbon
	 * @param HeadStartPos ribbon start position
	 * @param HeadEndPos ribbon end position
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void ReplayLinkLineHeadRibbon(FVector HeadStartPos, FVector HeadEndPos);

	/**
	* Replay single unit linkline animation
	*
	* @param ReplayLength CurrentReplayLength
	*/
	UFUNCTION(BlueprintCallable, Category = Visitor)
	void ReplaySingleLinkLineAniamtion(int32 ReplayLength);

	/**
	* Replay single unit linkline animation
	*
	* @param inPointsToStrighten Passed in points to straighten
	* @return The strightened points
	*/
	UFUNCTION(BlueprintCallable, Category = Visitor)
	TArray<int32> StraightenThePoints(TArray<int32> inPointsToStrighten);

	/**
	* Use static points to test the linkline ribbon animation
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void TestLinkLineRibbonAnimationUsingStaticPoints();

	/**
	* Use static segments to test the linkline ribbon animation
	* segments is just like points, but none of the three points in a line
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void TestLinkLineRibbonAnimationUsingStaticSegments();

	/** Linkline mode, the mode to display link line */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELinkLineMode LinkLineMode;

	/** Whether it is a static line. Test only, for static link lines.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStaticLine;

	/** Static line points. Test only, for static link lines.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> StaticLinePoints;
	
	/** Current tiles in the link line*/
	TArray<ASGTileBase*> LinkLineTiles;

protected:
	// The sprite asset for link corners 45 degree
	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UPaperSprite* Corner_45_Sprite;

	// The sprite asset for link corners 90 degree
	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UPaperSprite* Corner_90_Sprite;

	// The sprite asset for link corners 135 degree
	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UPaperSprite* Corner_135_Sprite;

	// The sprite asset for link body
	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UPaperSprite* BodySprite;

	/** Body sprites for render the link line body lines and coners */
	UPROPERTY(Category = Sprite, VisibleAnywhere, BlueprintReadOnly)
	TArray<UPaperSpriteComponent*> LinkLineSpriteRendererArray;

	/** Update link line sprites using the line points */
	bool UpdateLinkLineSprites(const TArray<int32>& LinePoints);

	// The ribbon ParticleSystem to display the linkline
	UPROPERTY(Category = Ribbon, EditAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"))
	UParticleSystem* LinkLineRibbonPS;

	// The ribbon emitter for display the linkline
	UPROPERTY(Category = Ribbon, EditAnywhere, BlueprintReadOnly)
	ASGLinkLineEmitter* LinkLineRibbonEmitter;

	/** Update link line ribbon using the line points */
	bool UpdateLinkLineRibbon(const TArray<int32>& LinePoints);

	/** Link line points, for drawing the sprites*/
	UPROPERTY(Category = LinePoints, VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> LinkLinePoints;

private:
	/** Head sprite for render the link line head */
	UPROPERTY(Category = Sprite, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess = "true"))
	UPaperSpriteComponent* HeadSpriteRenderComponent;

	/** Tail sprite for render the link line tail */
	UPROPERTY(Category = Sprite, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess = "true"))
	UPaperSpriteComponent* TailSpriteRenderComponent;

	UPaperSpriteComponent* CreateLineCorner(int inAngle, int inLastAngle);
	UPaperSpriteComponent* CreateLineSegment(int inAngle, bool inIsHead, bool inIsTail);

	int								m_CurrentSpriteNum;
	int								m_LastAngle;

	// Holds the messaging endpoint.
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;

	// Hold the reference to its parent grid
	ASGGrid* ParentGrid;

	/** Cached current turn collected tiles for do collect animation after replay link line animation */
	TArray<ASGTileBase*> CachedCollectTiles;

public:
	void ResetLinkState();
	void BuildPath(ASGTileBase* inNewTile);

};
