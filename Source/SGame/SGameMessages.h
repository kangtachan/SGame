#pragma once

#include "SGame.h"
#include "SGameMessages.generated.h"

/**
*/
USTRUCT()
struct FMessage_Gameplay_GameStart
{
	GENERATED_USTRUCT_BODY()
};

/**
*/
USTRUCT()
struct FMessage_Gameplay_GameOver
{
	GENERATED_USTRUCT_BODY()
};

/**
 * Player begin input event
*/
USTRUCT()
struct FMessage_Gameplay_PlayerBeginInput
{
	GENERATED_USTRUCT_BODY()
};

/**
 * Player end input event
*/
USTRUCT()
struct FMessage_Gameplay_PlayerEndInput
{
	GENERATED_USTRUCT_BODY()
};

/**
* Player end input event
*/
USTRUCT()
struct FMessage_Gameplay_NewTilePicked
{
	GENERATED_USTRUCT_BODY()

	/** The picked tile address */
	UPROPERTY()
	int32 TileAddress;
};

/**
* The tile selected status change event
*/
USTRUCT()
struct FMessage_Gameplay_TileSelectableStatusChange
{
	GENERATED_USTRUCT_BODY()

	/** The picked tile address, if the address is -1, then all apply to all tiles*/
	UPROPERTY()
	int32 TileAddress;

	/** The new selectable status, it can be override by the tile logic itself*/
	UPROPERTY()
	bool NewSelectableStatus;
};

/**
* The tile linked status change event
*/
USTRUCT()
struct FMessage_Gameplay_TileLinkedStatusChange
{
	GENERATED_USTRUCT_BODY()

	/** The picked tile address, if the address is -1, then all apply to all tiles*/
	UPROPERTY()
	int32 TileAddress;

	/** The new selectable status, it can be override by the tile logic itself*/
	UPROPERTY()
	bool NewLinkStatus;
};

/** Defines the game state */
UENUM()
namespace ESGGameStatus
{
	enum Type
	{
		EGS_Init,					// Initial value
		EGS_GameStart,				// Shield
		EGS_RondBegin,				// New round begin
		EGS_PlayerTurnBegin,		// Player turn begin
		EGS_PlayerRegengerate,		// Player regenerate
		EGS_PlayerSkillCD,			// Player regenerate
		EGS_PlayerInput,			// Player input, can link line or use the skill
		EGS_RoundEnd,				// End of the round
		EGS_GameOver,				// Game over
	};
}

/**
 * Game status update messages
*/
USTRUCT()
struct FMessage_Gameplay_GameStatusUpdate
{
	GENERATED_USTRUCT_BODY()

	/** The new game status */
	UPROPERTY()
	TEnumAsByte<ESGGameStatus::Type> NewGameStatus;
};