#pragma once

#include "CWorldQuery.h"
#include "SM_Network.h"
#include "IRMIMessageBody.h"

enum OpCode
{
	OP_MOVE = 0x0,
	OP_LOADK = 0x1,
	OP_LOADBOOL = 0x2,
	OP_LOADNIL = 0x3,
	OP_GETUPVAL = 0x4,
	OP_GETGLOBAL = 0x5,
	OP_GETTABLE = 0x6,
	OP_SETGLOBAL = 0x7,
	OP_SETUPVAL = 0x8,
	OP_SETTABLE = 0x9,
	OP_NEWTABLE = 0xA,
	OP_SELF = 0xB,
	OP_ADD = 0xC,
	OP_SUB = 0xD,
	OP_MUL = 0xE,
	OP_DIV = 0xF,
	OP_MOD = 0x10,
	OP_POW = 0x11,
	OP_UNM = 0x12,
	OP_NOT = 0x13,
	OP_LEN = 0x14,
	OP_CONCAT = 0x15,
	OP_JMP = 0x16,
	OP_EQ = 0x17,
	OP_LT = 0x18,
	OP_LE = 0x19,
	OP_TEST = 0x1A,
	OP_TESTSET = 0x1B,
	OP_CALL = 0x1C,
	OP_TAILCALL = 0x1D,
	OP_RETURN = 0x1E,
	OP_FORLOOP = 0x1F,
	OP_FORPREP = 0x20,
	OP_TFORLOOP = 0x21,
	OP_SETLIST = 0x22,
	OP_CLOSE = 0x23,
	OP_CLOSURE = 0x24,
	OP_VARARG = 0x25,
};

struct PickupParams
{
	EntityId itemPickupId;
};

struct RequestLeaveParams
{
	unsigned int actorId;
	Vec3 exitPos;
};

template <typename T>
struct _smart_ptr {
	T* p;
};

struct SClimbMessageExtra
{
	int type; //0x0000 
	int pad_0x04; //0x0004
	DWORD timestamp; //0x0008 
	int pad_0x10; //0x0010
	int pad_0x14; //0x0014
	int pad_0x18; //0x0018
	int flags; //0x001C
	Vec3 dir; //0x0020 
	Vec3 start; //0x002C 
	Vec3 end; //0x0038 
	bool isEnd; //0x0044 
};

using fnInvokeRMI = void(__fastcall*)(VOID*, int, int);
fnInvokeRMI oInvokeRMI;

/*
void __fastcall hkInvokeRMI(VOID* pBody, int where, int channel)
{
	auto body = *(CRMIBody**)pBody;
	std::cout << "objId: " << body->objId << std::endl;
	std::cout << "dependent: " << body->dependentId << std::endl;
	std::cout << body->pMessageDef->description << std::endl;

	return oInvokeRMI(pBody, where, channel);
}
*/
//VMTHookManager* pInvokeHook = new VMTHookManager();

using fnCreateHoldEntity = CRMIBodyImpl<SM_Network::SHoldEntityMessage>* (__fastcall*)(SGameObjectExtensionRMI*, unsigned int, SM_Network::SHoldEntityMessage*, __int64*, int, int);
fnCreateHoldEntity oHoldEntity;
CRMIBodyImpl<SM_Network::SHoldEntityMessage>* __fastcall fnCreateHold(SGameObjectExtensionRMI* method, unsigned int s, SM_Network::SHoldEntityMessage* msg, __int64* d, int u, int o)
{
	std::cout << "type: " << msg->type << std::endl;
	std::cout << "itemName: " << msg->itemName.m_str << std::endl;
	std::cout << "entityid: " << msg->entityId << std::endl;
	std::cout << "playerId: " << msg->playerId << std::endl;
	std::cout << "opcode: " << msg->opcode << std::endl;
	std::cout << "instant: " << msg->instant << std::endl;
	std::cout << "serverTime: " << msg->serverTime << std::endl;
	std::cout << "msgType: " << msg->msgType << std::endl;
	return oHoldEntity(method, s, msg, d, u, o);
}

enum ECommunicationEvent
{
	eCE_None = 0x0,
	//eCE_Quickchat_First = 0x1,
	eCE_SayNeedMedic = 0x2,
	eCE_SayNeedAmmo = 0x3,
	eCE_SayNeedArmor = 0x4,
	eCE_SayFollowMe = 0x5,
	eCE_SayCoverMe = 0x6,
	eCE_SayReady = 0x7,
	eCE_SayEnemySpotted = 0x8,
	eCE_SaySectorClear = 0x9,
	eCE_SayRegroup = 0xA,
	eCE_SayKeepMoving = 0xB,
	eCE_SayMoveOut = 0xC,
	eCE_SayFallBack = 0xD,
	eCE_SayAffirmative = 0xE,
	eCE_SayNegative = 0xF,
	eCE_SayEnemyDown = 0x10,
	eCE_SayTaunt = 0x11,
	//eCE_Quickchat_AfterLast = 0x11,
	eCE_SayOverHere = 0x12,
	eCE_SendingEnemyCoord = 0x13,
	eCE_EnemySpotted = 0x14,
	eCE_ClaymoreSpotted = 0x15,
	eCE_GrenadeSpotted = 0x16,
	eCE_HelpToPush = 0x17,
	eCE_LiftMeOn = 0x18,
	eCE_FollowMe = 0x19,
	eCE_FireInTheHole = 0x1A,
	eCE_FlagPickup = 0x1B,
	eCE_FlagDrop = 0x1C,
	eCE_FlagReturn = 0x1D,
	eCE_CaptureStart = 0x1E,
	eCE_CaptureEnd = 0x1F,
	eCE_BombPickup = 0x20,
	eCE_BombDrop = 0x21,
	eCE_BombDropManual = 0x22,
	eCE_BombPlant = 0x23,
	eCE_BombDefuse = 0x24,
	eCE_StopBombDefuse = 0x25,
	eCE_EnemyDown = 0x26,
	eCE_DeathRattle = 0x27,
	eCE_OutOfAmmo = 0x28,
	eCE_TakeAmmo = 0x29,
	eCE_ResupplyAmmo = 0x2A,
	eCE_ResupplyMedkit = 0x2B,
	eCE_ResupplyWeapons = 0x2C,
	eCE_HealingSelf = 0x2D,
	eCE_RepairingSelf = 0x2E,
	eCE_HealingTeammate = 0x2F,
	eCE_RepairingTeammate = 0x30,
	eCE_BeingHealed = 0x31,
	eCE_BeingRepaired = 0x32,
	eCE_ImDown = 0x33,
	eCE_SniperSpotted = 0x34,
	eCE_SoldierSpotted = 0x35,
	eCE_ShieldBearerSpotted = 0x36,
	eCE_IronManSpotted = 0x37,
	eCE_SniperDown = 0x38,
	eCE_SoldierDown = 0x39,
	eCE_ShieldBearerDown = 0x3A,
	eCE_IronManDown = 0x3B,
	eCE_EnemyDamaged = 0x3C,
	eCE_PickedReward = 0x3D,
	eCE_PickedScore = 0x3E,
	eCE_PickedIngameCurrency = 0x3F,
	eCE_ClassSelectedIngame = 0x40,
	eCE_TeammateProtected = 0x41,
	eCE_CoreStartUse = 0x42,
	eCE_AIKnockBack = 0x43,
	eCE_PlayerEnteredSession = 0x44,
	eCE_PlayerLeftSession = 0x45,
	eCE_Last = 0x46,
};

struct CommunicationEventParams
{
	ECommunicationEvent eventType;
	unsigned int source;
	unsigned int target;
	CryStringT strParam;
	int intParam;
};


class CGameObject
{
public:
	using fnSendMessage = void(__stdcall*)(CGameObject*, __int64, __int64, SM_Network::SHoldEntityMessage*);
	void SendMessageFromClient(SM_Network::SHoldEntityMessage* msg) { return fnSendMessage(0x141720780)(this, 0x142175008, 0x142175000, msg); }

	fnCreateHoldEntity pGetValue = reinterpret_cast<fnCreateHoldEntity>(0x141750EF0);

	void InstallHook()
	{
		//MH_Initialize();
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		fnCreateHoldEntity pGetValue = reinterpret_cast<fnCreateHoldEntity>(0x141750EF0);

		//if (ReplaceCall((void*)0x141750EF0, (void*)fnCreateHold, (long long*)oHoldEntity))
		//{
			//std::cout << "Installed hook!" << std::endl;
		//}

		//if (MH_CreateHook(reinterpret_cast<void**>(pGetValue), &fnCreateHold, (reinterpret_cast<void**>(&oHoldEntity))) != MH_OK || MH_EnableHook(reinterpret_cast<void**>(pGetValue)) != MH_OK)
		//{
			//std::cout << "Can't install hook" << std::endl;
		//}
		//else
		//{
			//std::cout << "Installed hook!" << std::endl;
		//}
	}

	void InvokeRMI(VOID** pBody, int iRMI, int channel) { VirtualFunction<void(__fastcall*)(VOID*, VOID**, int, int)>(this, 448 / 8)(this, pBody, iRMI, channel); }
	template <typename T>
	void InvokeRMI(CRMIBodyImpl<T>** pBody, int iRMI, int channel) { VirtualFunction<void(__fastcall*)(VOID*, CRMIBodyImpl<T>**, int, int)>(this, 448 / 8)(this, pBody, iRMI, channel); }
	void DoInvokeRMI(void* pBody, int iRMI, int channel) { VirtualFunction<void(__fastcall*)(void*, void*, int, int)>(this, 448 / 8)(this, pBody, iRMI, channel); }
	CWorldQuery* GetWorldQuery() { return VirtualFunction<CWorldQuery* (__thiscall*)(void*)>(this, 51)(this); }
	uint16 GetChannelId() { return VirtualFunction<uint16(__thiscall*)(void*)>(this, 104 / 8)(this); }
	int GetEntityId() { return *(int*)((uint64_t)this + 0x8);}

	template <typename T>
	using fnCreateFunction = CRMIBodyImpl<T>* (__fastcall*)(SGameObjectExtensionRMI*, unsigned int, T*, __int64*, int, int);
	template <typename T>
	CRMIBodyImpl<T>* CreateFunction(T pMessage, DWORD64 dwAddres, DWORD64 dwAllocator)
	{
		return fnCreateFunction<T>(dwAddres)(*(SGameObjectExtensionRMI**)dwAllocator, GetEntityId(), &pMessage, nullptr, 0, 0);
	}

	using fnClimb = CRMIBodyImpl<SM_Network::SClimbMessage>* (__fastcall*)(SGameObjectExtensionRMI*, unsigned int, SM_Network::SClimbMessage*, __int64*, int, int);
	CRMIBodyImpl<SM_Network::SClimbMessage>* CreateClimbBody(SM_Network::SClimbMessage* pMessage)
	{
		return fnClimb(0x1416B6950)(*(SGameObjectExtensionRMI**)0x1424ECCE8, GetEntityId(), pMessage, nullptr, 0, 0);
	}

	using fnKnockBackMessage = CRMIBodyImpl<SM_Network::SKnockBackMessage>* (__fastcall*)(SGameObjectExtensionRMI*, unsigned int, SM_Network::SKnockBackMessage*, __int64*, int, int);
	CRMIBodyImpl<SM_Network::SKnockBackMessage>* CreateKnockbackBody(SM_Network::SKnockBackMessage* pMessage)
	{
		return fnKnockBackMessage(0x1416BC0B0)(*(SGameObjectExtensionRMI**)0x1424ECD18, GetEntityId(), pMessage, nullptr, 0, 0);
	}

	void SendClimbMessageFromClient(Vec3 vPos, int type, int channel = -1)
	{
		SM_Network::SClimbMessage message;
		message.type = SM_Network::ESMType::eSMT_Climb;
		message.helperClosestPoint = vPos;
		message.animStartPose.q.v = vPos;
		message.animStartPose.t = vPos;
		message.animFinished = true;
		message.msgType = SM_Network::EMessageType::eMT_End;
		message.instant = 1;
		message.opcode = 0;
		message.animIndex = EClimbAnim::eCA_Middle;

		CRMIBodyImpl<SM_Network::SClimbMessage>* result = this->CreateFunction<SM_Network::SClimbMessage>(message, 0x14152FB40, 0x1421AF348);
		if (result)
		{
			_InterlockedIncrement((volatile unsigned __int32*)((__int64)result + 0x38));
			this->InvokeRMI<SM_Network::SClimbMessage>(&result, type, channel);
		}
	}

	bool SendRequest(SM_Network::ESMType type, void* message)
	{
		switch (type)
		{
			case SM_Network::ESMType::eSMT_Climb:
			{
				CRMIBodyImpl<SM_Network::SClimbMessage>* result = this->CreateClimbBody((SM_Network::SClimbMessage*)message);
				auto method = result;
				if (result)
				{
					_InterlockedIncrement((volatile unsigned __int32*)((__int64)method + 0x38));

					this->InvokeRMI<SM_Network::SClimbMessage>(&result, 256, -1);

					return true;
				}
			}

			case SM_Network::ESMType::eSMT_KnockBack:
			{
				CRMIBodyImpl<SM_Network::SKnockBackMessage>* result = this->CreateKnockbackBody((SM_Network::SKnockBackMessage*)message);
				auto method = result;
				if (result)
				{
					_InterlockedIncrement((volatile unsigned __int32*)((__int64)method + 0x38));

					this->InvokeRMI<SM_Network::SKnockBackMessage>(&result, 256, -1);

					return true;
				}
			}
		}
	}


	// E8 ? ? ? ? 48 89 44 24 ? 48 85 C0 74 04 F0 FF 40 38 41 B8 ? ? ? ? EB 26 33 C0 48 8B CB 89 44 24 28 89 44 24 20 E8 ? ? ? ? 48 89 44 24 ? 48 85 C0 74 04 F0 FF 40 38 41 B8 ? ? ? ? 

	//using fnCreate = void*(__fastcall*)(void*, unsigned int, SM_Network::SHoldEntityMessage*, void*, int, int);

	//void Create(SM_Network::SHoldEntityMessage msg) {
		//auto method = fnCreate(0x14171F1D0)(*(void**)0x142172FF0, *(EntityId*)((std::uintptr_t)this + 0x8), &msg, nullptr, 0, 0); // outdated
		//if(method)this->DoInvokeRMI(&method, 256, -1);
	//}

};