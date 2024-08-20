#pragma once
// author - saurux | 2023
// discord: _saurux

#include "CEntity.h"
#include "CGameObject.h"
#include "CItemProxy.h"
#include "CMovementController.h"
#include "CInventory.h"
#include "SM_Network.h"
#include "CActorInventory.h"
#include "CPhysicalWorld.h"
#include "CActorAnimation.h"


class CActor;

struct PosParams
{
	Vec3 pos;
};

struct TeleportParams
{
	EntityId to;
	Vec3 pos;
	Quat_tpl<float> rot;
	bool teleportToGroup;
	bool setPhysPos;
};

enum ESafeCapsuleType
{
	eSCT_General = 0x0,
	eSCT_Vault = 0x1,
};


struct SDebugInfo
{
	Vec3 delta;
	float tangentCoeff;
	float velocity;
};

struct CSafeCapsule
{
	ESafeCapsuleType m_type;
	IPhysicalEntity* m_pPhysics;
	Vec3 m_prevAttractPoint;
	float m_originalCenterHeight;
	float m_standCenterHeight;
	SDebugInfo m_debugInfo;
};

enum EUpdateMode
{
	eUM_EXCLUSIVE = 0x0,
	eUM_MUTATOR = 0x1,
};

struct KnockBackHitInfo
{
	float chance;
	float staminaDamage;
	CryStringT hitType;
	Vec3 impactDir;
	unsigned int shooterId;
};


struct __declspec(align(8)) SSpecialMovementState
{
	SM_Network::ESMType activeSM;
	EUpdateMode activeSMUpdateMode;
	SM_Network::ESMType prevSM;
	SM_Network::ESMType interruptedSM;
	bool useViewLimits;
	Vec3 viewLimitDir;
	float horzLimitAngle;
	float vertLimitAngleMin;
	float vertLimitAngleMax;
	bool useViewOffset;
	Vec3 viewOffset;
	bool useRoll;
	float rollAngle;
	bool useStance;
	EStance smStance;
	CSafeCapsule* pSafeCapsule;
	bool interruptHaste;
	bool restartHaste;
	bool hasteAwaitingRestart;
	unsigned __int16 hasteInterruptFlags;
	float hasteCurTime;
	float hasteTimeMult;
	float hasteSpeedMult;
	float slideDistanceMult;
	float minStaminaToStartHaste;
	bool setFinalStance;
	Vec3 slideDir;
	float climbExtraHeight;
	CryStringT interactionAction;
	float interactionTime;
	float interactionServerTime;
	unsigned int interactionTrigger;
	bool isInteractionActionActive;
	unsigned int holdEntity;
	CryStringT holdEntityItemName;
	bool isHoldEntityAttached;
	DWORD64 LocalAnimStartTime;
	bool holsterOutAfterSMEnd;
	std::vector<::KnockBackHitInfo, std::allocator<::KnockBackHitInfo> > knockBackHits;
	float knockBackResistance;
	float knockBackStaminaDamage;
	unsigned int knockBackShooterId;
	bool knockBackFallingFinished;
	bool setRaiseAssistState;
	bool setStunned;
	bool isStunned;
	CryStringT hitType;
	bool setAssistState;
	unsigned int setAssister;
	bool waitingInAssist;
	Vec3 coopExactDir;
	SM_Network::Lineseg_tpl coopEdge;
	bool coopSingle;
	bool coopClimbFeedback;
	bool coopAssistFeedback;
	bool coopEnterAssistFeedback;
	bool interruptFeedback;
	bool raiseAssistFeedback;
	DWORD64 interruptTime;
	float coopScoreCoolDownTime;
	float raiseScoreCoolDownTime;
	Vec3 animStartPos;
	Vec3 helperClosestPoint;
	bool turnSpeedScale;
};

struct SFPViewParams
{
	Vec3 m_eyeOffsetView;
	Vec3 m_bobOffset;
	Vec3 m_FPWeaponLastDirVec;
	float smoothViewZ;
	Vec3 spectatorTargetPos;
	Vec3 spectatorCamPos;
	float spectatorPosZ;
	Vec3 deathCamPlayerPos;
	Vec3 deathCamKillerPrevPos;
	Quat_tpl<float> deathCamView;
	Quat_tpl<float> deathCamKillView;
	float deathCamKillerFov;
};

class CFPPlayer
{
public:
	SFPViewParams m_FPViewParams;
	//char pad_0x0000[0x84];
	Quat_tpl<float> m_viewQuat;
	Quat_tpl<float> m_viewQuatFinal;
	Quat_tpl<float> m_baseQuat;

	Quat_tpl<float> GetFinalRotation() { return *(Quat_tpl<float>*)((DWORD64)this + 0x94); }
	Vec3 GetWeaponPosition() {  return *(Vec3*)((DWORD64)this + 0xC4); }

	void SetWeaponPosition(Vec3 vPosition) { *(Vec3*)((DWORD64)this + 0xC4) = vPosition; }
};

class CAnimationState
{
private:
	char pad_0x0000[0xC];
	BYTE m_pCurrentState;
public:
	void SendState(const char* animInput) { VirtualFunction<void(__thiscall*)(void*, BYTE, const char**, DWORD64)>(this, 1)(this, this->m_pCurrentState, &animInput, 0); }
};

class CAnimationSystem
{
private:
	char pad_0x0000[0xC8];
	CAnimationState* m_pAnimState;
public:
	/* Анимации:
	climb
	knockBack
	raiseAssist
	vault
	coopCinematic
	coopClimb
	coopAssist
	interactionAction
	holdEntity
	ropeClimb
	*/
	CAnimationState* GetAnimationState() { return this->m_pAnimState; /*VirtualFunction<CAnimationState* (__thiscall*)(void*)>(this, 200 / 8)(this);*/ } // return this->m_pAnimState;
	void SendAnimationState(const char* animInput) { if (CAnimationState* pAnimationState = this->GetAnimationState()) { pAnimationState->SendState(animInput); } }
};

class CSpotting
{
public:
	bool IsSpotted(CEntity* pEntity)
	{
		return CallFunction<bool(__fastcall*)(CSpotting*, CEntity*)>(0x14138B9D0)(this, pEntity); // enemy_spotted_by_vision
	}
};

class CBaseSpectatorMode
{
public:
	float GetSpectatorHorizontalAngle() { return VirtualFunction<float(__fastcall*)(void*)>(this, 0x28 / 8)(this); }
	float GetSpectatorVerticalAngle() { return VirtualFunction<float(__fastcall*)(void*)>(this, 0x30 / 8)(this); }
};

class CPlayerSpectator
{
public:
	char pad_0x0010[0x10];
	std::unique_ptr< CBaseSpectatorMode, std::default_delete<CBaseSpectatorMode>> m_pMode;
	bool m_isThirdPerson;
	int m_friendlyTeam;
};

struct SHitParticleAttInfo
{
	CryStringT name;
	DWORD64 creationTime;
	DWORD64 lifeTime;
};

class ICompoundBase
{
public:

};

struct CHitParticleAtt
{
	std::vector<SHitParticleAttInfo, std::allocator<SHitParticleAttInfo>> m_particleAtt;
	CActor* m_owner;
	int m_attCount;
};

struct SStaminaInitParams
{
	float m_regenJump;
	float m_jumpCost;
	float m_maxStamina;
	float m_lowStaminaLevel;
	float m_regenProne;
	float m_regenCrouch;
	float m_regenStand;
	float m_regenWalk;
	float m_regenKnockback;
	float m_accelMult;
	float m_hasteVelLim;
	float m_hasteFastAccelMult;
	float m_knockbackStandThreshold;
};

class CPlayerGameProfiles
{
public:
	char pad_0x0008[0x8];
	SStaminaInitParams m_params;
};

class CMeshManager
{
public:
	void RemoveMesh(const char* name) { VirtualFunction<void(__fastcall*)(void*, const char*)>(this, 40 / 8)(this, name); }
};

class CActorMesh
{
public:
	CMeshManager* GetMeshManager() { return VirtualFunction<CMeshManager* (__fastcall*)(void*)>(this, 56 / 8)(this); }
};

class CCompoundBase
{
public:
	CActorMesh* GetActorMesh() { return VirtualFunction<CActorMesh*(__fastcall*)(void*)>(this, 16 / 8)(this); }
};

class CActor
{
public:
	using fnReportActiveSM = void(__stdcall*)(CActor*, SM_Network::ESMType);
	using fnResetAnimGraph = void(__fastcall*)(CActor*);

	CEntity* GetEntity() { return *(CEntity**)((uint64_t)this + 0x10); }
	CGameObject* GetGameObject() { return *(CGameObject**)((uint64_t)this + 0x18); }
	EntityId GetEntityId() { return *(EntityId*)((uint64_t)this + 0x20); }
	uint32_t GetTeamId() { return *(uint32_t*)((uint64_t)this + 0x3E0); }
	int GetClassId() { return *(int*)((uint64_t)this + 0x458); }
	BYTE IsLocal() { return *(BYTE*)((uint64_t)this + 0xCE4); }
	BYTE PhysCounter() { return *(BYTE*)((uint64_t)this + 0xCE4); }
	int GetHealth() { return VirtualFunction<int(__thiscall*)(void*)>(this, 224 / 8)(this); }
	int GetArmor() { return VirtualFunction<int(__thiscall*)(void*)>(this, 256 / 8)(this); }
	bool IsDead() { return GetHealth() <= 0; }
	void SetThirdPerson(bool bValue) { VirtualFunction<void(__thiscall*)(void*, bool)>(this, 67)(this, bValue); }
	void SetViewRotation(Quat qRotation) { VirtualFunction<void(__thiscall*)(void*, Quat)>(this, 416 / 8)(this, qRotation); } // OnActorStandUp
	Quat GetViewRotation() { return VirtualFunction<Quat(__thiscall*)(void*)>(this, 408 / 8)(this); } // OnActorStandUp
	//Quat GetViewRotation(Quat_tpl<float>* qResult) { return VirtualFunction<Quat(__thiscall*)(void*, Quat_tpl<float>*)>(this, 424 / 8)(this, qResult); } // OnActorStandUp
	CSpotting* GetSpottingEntity() { return *(CSpotting**)((uint64_t)this + 0x11A0); }
	//Quat GetViewRotation() { return this->GetEntity()->GetEntityRotation(); }
	void SetSpectatorMode(EActorSpectatorMode mode, EntityId targetId) { VirtualFunction<void(__thiscall*)(void*, EActorSpectatorMode, EntityId)>(this, 928 / 8)(this, mode, targetId); }
	CItemProxy* GetCurrentItem(bool includeVehicle = false) { return VirtualFunction<CItemProxy*(__thiscall*)(void*, bool)>(this, 464 / 8)(this, includeVehicle); }
	CMovementController* GetMovementController() { return VirtualFunction<CMovementController* (__thiscall*)(void*)>(this, 496 / 8)(this); } // GetHeadDir
	CActorAnimation* GetActorAnimation() { return VirtualFunction<CActorAnimation* (__thiscall*)(void*)>(this, 656 / 8)(this); }
	CAnimationSystem* GetAnimationSystem() { return VirtualFunction<CAnimationSystem* (__thiscall*)(void*)>(this, 664 / 8)(this); }
	CInventory* GetInventory() { return VirtualFunction<CInventory* (__thiscall*)(void*)>(this, 472 / 8)(this);}
	bool IsClient() { return VirtualFunction<bool (__thiscall*)(void*)>(this, 576 / 8)(this);} // OnActorSitDown
	CActorInventory* GetActorInventory() { return *(CActorInventory**)((uint64_t)this + 0x408); } // hideout_custom
	CFPPlayer* GetCFFPlayer() { return *(CFPPlayer**)((uint64_t)this + 0xD10); }
	CPlayerGameProfiles* GetPlayerGameProfiles() { return *(CPlayerGameProfiles**)((uint64_t)this + 0x12E8); }
	CPlayerSpectator* GetPlayerSpectator() { return *(CPlayerSpectator**)((uint64_t)this + 0xD18); }
	Vec3 GetPosition() { return this->GetEntity()->GetPosition(); }
	void SetPosition(Vec3 vPosition) { return this->GetEntity()->SetPosition(vPosition, 0x1); }
	void EnableParticleImpulseReact(bool bCant) { VirtualFunction<void(__thiscall*)(void*, bool)>(this, 736 / 8)(this, bCant); }
	void SetModelName(const char* modelName) { VirtualFunction<void(__thiscall*)(void*, const char*)>(this, 616 / 8)(this, modelName); } // 1320
	Vec3 GetForwardDir() { return this->GetEntity()->GetForwardDir(); }
	CAnimationGraphState* GetAnimationGraphState() { return VirtualFunction<CAnimationGraphState*(__thiscall*)(void*)>(this, 37)(this); }
	CHitParticleAtt* GetHitParticle() { return this->Get<CHitParticleAtt*>(0xA38); }
	CCompoundBase* GetCompoundBase() { return this->Get<CCompoundBase*>(0xA08); }
	void ResetAnimGraph() { return fnResetAnimGraph(0x141231DC0)(this); } // ResultCameraA first xref v1 + 8

	void ReportActiveSM(SM_Network::ESMType type)
	{
		const char* sAnimName;
		switch (type)
		{
		case SM_Network::eSMT_None:
			sAnimName = "SMNone";
			break;
		case SM_Network::eSMT_Haste:
			sAnimName = "SMHaste";
			break;
		case SM_Network::eSMT_Climb:
			sAnimName = "SMClimb";
			break;
		case SM_Network::eSMT_Slide:
			sAnimName = "SMSlide";
			break;
		case SM_Network::eSMT_KnockBack:
			sAnimName = "SMKnockBack";
			break;
		case SM_Network::eSMT_RaiseAssist:
			sAnimName = "SMRaiseAssist";
			break;
		case SM_Network::eSMT_Vault:
			sAnimName = "SMVault";
			break;
		case SM_Network::eSMT_CoopClimb:
			sAnimName = "SMCoopClimb";
			break;
		case SM_Network::eSMT_CoopAssist:
			sAnimName = "SMCoopAssistDouble";
			break;
		case SM_Network::eSMT_RopeClimb:
			sAnimName = "SMRopeClimb";
			break;
		}

		this->GetEntity()->SendEvent(sAnimName, this);
	}

	void DoInvokeRMI(void* msg)
	{
		auto pItem = this->GetCurrentItem();
		if (!pItem) return;
		auto pGameObject = pItem->GetGameObject();
		if (!pGameObject) return;
		pGameObject->InvokeRMI(&msg, 256, -1);
	}

	SSpecialMovementState GetMovementState() { return *(SSpecialMovementState*)((DWORD64)this + 0xF98); }

	using fnCall = void(__stdcall*)(CActor*, void*, void*, int, int);
	void RequestMessage(DWORD64 dwAdress, DWORD64 dwAllocator, void* pMessage) { return fnCall(dwAdress/*function*/)(this, *reinterpret_cast<void**>(dwAllocator)/*allocator*/, pMessage, 0x100, 0xFFFFFFFF); }

	template <class T>
	inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }
	template <class T>
	inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }
};

namespace MovementCore {

	struct SMovementCmd {

		unsigned int N;
		unsigned __int8 physCounter;
		Vec3 lookDir;
		Vec3 slideDir;
		Vec3 moveDir;
		bool haste;
		bool slide;
		bool jump;
		bool use;
		bool zoom;
		bool simulate;
		char stance;
		unsigned int stateChecksum;
		bool generated;
	};

	struct SMovementCmdBucket {

		unsigned int N;
		unsigned __int8 physCounter;
		unsigned int stateChecksum;
		std::vector< MovementCore::SMovementCmd, std::allocator< MovementCore::SMovementCmd > > commands;
	};

	struct SPlayerMovementState {

		unsigned int cmdN;
		unsigned __int8 physCounter;
		bool hasData;
		unsigned int standingOn;
		Vec3 pos;
		Vec3 vel;
		Vec3 slideDir;
		float slideTimer;
		char stance;
		bool inHaste;
		bool inSlide;
		bool inJump;
		bool inZoom;
		bool simulate;
		bool isRemotePlayer;
		bool isExtrapolated;
		float stamina;
		float groundTimer;
		Vec3 filteredMove;
		Vec3 groundNormal;
		Vec3 lookDirection;
		float latency;
		float pseudoSpeed;
		bool isStuck;
		Vec3 moveDir;
	};

	using fnMove = void(__fastcall*)(CActor*, MovementCore::SMovementCmd*, MovementCore::SPlayerMovementState*, MovementCore::SPlayerMovementState*);
	fnMove oMove;

	void hkMove(/* CPlayer */ CActor* player, MovementCore::SMovementCmd* cmd, MovementCore::SPlayerMovementState* in_state, MovementCore::SPlayerMovementState* out_state) {
		
		cmd->jump = false;
		cmd->slide = false;
		oMove(player, cmd, in_state, out_state);
	}

	using fnMove = void(__fastcall*)(CActor*, MovementCore::SMovementCmd*, MovementCore::SPlayerMovementState*, MovementCore::SPlayerMovementState*);
	void Move(/* CPlayer */ CActor* player, MovementCore::SMovementCmd* cmd, MovementCore::SPlayerMovementState* in_state, MovementCore::SPlayerMovementState* out_state) {
		fnMove(0x14143D030)(player, cmd, in_state, out_state);     // Find -> ClientMove
	}
}