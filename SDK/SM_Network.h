#pragma once

struct StrHeader
{
	volatile int nRefCount;
	int nLength;
	int nAllocSize;
};

struct CryStringT
{
	const char* m_str;
	int* m_header;
};

struct CryStringV
{
	const char* m_str;
	StrHeader* m_header;
};

enum EClimbAnim
{
	eCA_None = 0xFFFFFFFF, // Краш сервера
	eCA_Lower = 0x0, // Невидимость
	eCA_Middle = 0x1, // Хуйня
	eCA_Upper = 0x2, // Десинхрон
	eCA_Double = 0x3, // Десинхрон
	eCA_NumAnims = 0x4, // Краш игроков
};

enum ENetworkOpcode
{
	eNO_Start = 0x0,
	eNO_End = 0x1,
};

enum EKnockBackNetworkOpcode
{
	eNO_StartFalling = 0x0,
	eNO_StartIdle = 0x1,
	eNO_StartRaiseSingle = 0x2,
	eNO_SetRaiseCoop = 0x3,
	eNO_EndKnockBack = 0x4,
	eNO_Stunned = 0x5,
};

struct CEidSerializer
{
	unsigned int m_id;
	bool m_valid;
};

class SMessageHandler;

class SMessageHandler
{
public:
	static SMessageHandler* Singleton() { return *(SMessageHandler**)0x141C0B388; } // unk_141C0B388
};

class SM_Network
{
public:
	enum ESMType
	{
		eSMT_None = 0xFFFFFFFF,
		eSMT_Haste = 0x0,
		eSMT_Climb = 0x1,
		eSMT_Slide = 0x2,
		eSMT_KnockBack = 0x3,
		eSMT_RaiseAssist = 0x4,
		eSMT_Vault = 0x5,
		eSMT_CoopCinematic = 0x6,
		eSMT_CoopClimb = 0x7,
		eSMT_CoopAssist = 0x8,
		eSMT_InteractionAction = 0x9,
		eSMT_HoldEntity = 0xA,
		eSMT_RopeClimb = 0xB,
		eSMT_NumAnims = 0xC,

		// TEST
		eSMT_Invalid = 0xFFFFFFF,
	};

	static enum EMessageType
	{
		eMT_None = 0xFFFFFFFF,
		eMT_Start = 0x0,
		eMT_End = 0x1,
		eMT_Message = 0x2,

		eMT_Unknown = 0x80000000,
		// TEST
		eMT_Invalid = 0xFFFFFFF,
	};

	static enum EStance
	{
		STANCE_NULL = 0xFFFFFFFF,
		STANCE_STAND = 0x0,
		STANCE_CROUCH = 0x1,
		STANCE_PRONE = 0x2,
		STANCE_STEALTH = 0x3,
		STANCE_LOW_COVER = 0x4,
		STANCE_HIGH_COVER = 0x5,
		STANCE_PATROL = 0x6,
		STANCE_RANGE = 0x7,
		STANCE_LAST = 0x8,
	};

	static struct SMessage
	{
		SMessageHandler* handle;
		ESMType type;
		EMessageType msgType;
		DWORD64 serverTime;
		int opcode;
		bool instant;
	};

	static struct SKnockBackMessage : SM_Network::SMessage
	{
		Quat_tpl<float> animStartLocalRot;
		Vec3 startPos;
		CEidSerializer standingOn;
	};

	static struct SRaiseAssistMessage : SM_Network::SMessage
	{
		EntityId targetId;
	};

	static struct SInteractionActionMessage : SM_Network::SMessage
	{
		CryStringT action;
		float interactionTime;
		EStance stance;
		unsigned int interactionTrigger;
		Vec3 moveToPos;
		Vec3 lookAtPos;
		unsigned int attachmentId;
		CryStringT attachmentModel;
		bool attachModelOnStart;
		bool holsterInBeforeAction;
		bool holsterOutAfterAction;
	};

	static struct SHoldEntityMessage : SM_Network::SMessage
	{
		unsigned int entityId;
		unsigned int playerId;
		CryStringT itemName;
	};

	static struct SVaultMessage  : SM_Network::SMessage
	{
		EClimbAnim animIndex;
		QuatT_tpl<float> animStartPose;
		Vec3 helperClosestPoint;
		bool animFinished;
	};

	static struct SSlideMessage : SM_Network::SMessage
	{
		Vec3 slideDir;
		bool finishInCroush;
	};

	static struct Lineseg_tpl
	{
		Vec3 start;
		Vec3 end;
	};

	static struct SCoopAssistMessage : SM_Network::SMessage
	{
		EClimbAnim animIndex;
		bool singleClimb;
		Vec3 animStartPos;
		Vec3 helperClosestPoint;
		EntityId climber;
		Lineseg_tpl edge;
		DWORD64 ServerStartFrame;
	};

	static struct SCoopCinematicMessage : SM_Network::SMessage
	{
		EntityId locatorId;
	};

	static struct SCoopClimbMessage : SM_Network::SMessage
	{
		EntityId targetId;
	};

	static struct SClimbMessage : SM_Network::SMessage
	{
		int animIndex;
		QuatT_tpl<float> animStartPose;
		Vec3 helperClosestPoint;
		bool animFinished;
	};
};