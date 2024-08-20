#pragma once

#include "CActor.h"
#include "PTBGameRules.h"

class IGameHitListener
{
public:
	virtual void OnHit(SGameClientHitInfo* hitInfo) {};
	virtual void OnExplosion(SGameClientHitInfo* hitInfo) {};
	virtual void OnServerExplosion(SGameClientHitInfo* hitInfo) {};
};

class CHitListener : public IGameHitListener
{
public:
	void OnHit(SGameClientHitInfo* hitInfo)
	{
		std::cout << hitInfo->bulletType << std::endl;
	}
};

struct SMarkerParams
{
	unsigned int m_entity;
	Vec3 m_pos;
};

struct SObjectiveStateFeedback
{
	CryStringT first_message;
	CryStringT second_message;
	CryStringT message_lifetime;
	CryStringT soundName;
};

enum EMissionObjectiveState
{
	eMOS_Deactivated = 0x0,
	eMOS_Activated = 0x1,
	eMOS_Completed = 0x2,
	eMOS_Failed = 0x3,
	eMOS_NumStates = 0x4,
};

struct SMissionObjective : SMarkerParams
{
	CryStringT name;
	CryStringT description;
	CryStringT type;
	CryStringT team;
	SObjectiveStateFeedback feedback[4];
	int markerId;
	EMissionObjectiveState state;
};

class CMissionObjectives
{
public:
	std::map<CryStringT, SMissionObjective, std::less<CryStringT>, std::allocator<std::pair<CryStringT const, SMissionObjective> > > m_objectives;
};

struct SActorHitValidationStats
{
	int m_totalHits;
	int m_rejectedHits;
	CryStringT m_name;
};

class CHitValidationStatistics
{
public:
	int m_totalHits;
	int m_rejectedHits;
	std::map<unsigned int, SActorHitValidationStats, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, SActorHitValidationStats> > > m_actorStats;
};

class CMissionStatistics
{
public:
	// sub_141445090
};

class CAchievementsTracker
{
public:
	char pad_0x0008[0x10];
	CMissionStatistics* m_pMissionStatistics;
};

class CGameRules
{
private:
	char pad_0x0440[0x450]; // BombEntity -> xref 2
	PTBGameRules* pTBGameRules;

	using fnAddHitListener = void(__fastcall*)(CGameRules*, IGameHitListener*);
public:
	// 0x228
	CHitValidationStatistics* GetHitValidationStatistics() { return *(CHitValidationStatistics**)((uintptr_t)this + 0x228); }
	int GetTeam(int entityId) { return VirtualFunction<int(__thiscall*)(void*, int)>(this, 110)(this, entityId); }
	void ClientHit(SGameClientHitInfo* hitInfo) { VirtualFunction<int(__thiscall*)(void*, SGameClientHitInfo*)>(this, 159)(this, hitInfo); }
	void ClientHit(SClientGameHitInfo* hitInfo) { VirtualFunction<int(__thiscall*)(void*, SClientGameHitInfo*)>(this, 159)(this, hitInfo); }
	int GetHitTypeId(const char* name) { return VirtualFunction<int(__thiscall*)(void*, const char*)>(this, 328 / 8)(this, name); }
	int GetHitMaterialId(const char* name) { return VirtualFunction<int(__thiscall*)(void*, const char*)>(this, 0x3A8 / 8)(this, name); }
	void IncreasePassedCheckpoints(int i) { VirtualFunction<void(__thiscall*)(void*, int)>(this, 488 / 8)(this, i); }
	bool IsNotMyTeam(int m_Id, int p_Id) { return (this->GetTeam(m_Id) != this->GetTeam(p_Id) || this->GetTeam(m_Id) == 0); }
	void SendCommunicationEvent(EntityId playerId, ECommunicationEvent events, EntityId entityId = 0) { VirtualFunction<void(__fastcall*)(CGameRules*, ECommunicationEvent, EntityId, EntityId, const char*, int)>(this, 0x2E8 / 8)(this, events, playerId, entityId, u8"ƒмитрий_ рымский", 0); }
	PTBGameRules* GetPTBGameRules() { return this->pTBGameRules; }
	CMissionObjectives* GetMissionObjectives() { return  *(CMissionObjectives**)((uintptr_t)this + 0x318); }
	CAchievementsTracker* GetAchievementsTracker() { return  *(CAchievementsTracker**)((uintptr_t)this + 0x3C8); }
	void ResurrectByCoin(EntityId entityId) { return CallFunction<void(__fastcall*)(void*, EntityId)>(0x141190510)(this, entityId); }
	void RequestClassChange(ECharacterClassId classId) { CallFunction<void(__fastcall*)(CGameRules*, ECharacterClassId)>(0x1410AC4B0)(this, classId); }
	unsigned int GetChannelId(EntityId entityId) { return CallFunction<unsigned int(__fastcall*)(CGameRules*, EntityId)>(0x14109DAF0)(this, entityId); }
	void AddHitListener(IGameHitListener* l) { fnAddHitListener(0x1410ABB70)(this, l); }
};