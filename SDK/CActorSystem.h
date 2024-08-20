#pragma once

#include "CActor.h"

class CActorSystem
{
public:
	int CreateActor(__int16 channelId, const char* name, const char* actorClass, Vec3* vPos, Quat* rot, Vec3* scale, EntityId id) { return VirtualFunction<int (__thiscall*)(void*, __int16, const char*, const char*, Vec3*, Quat*, Vec3*, EntityId)>(this, 0x58 / 8)(this, channelId, name, actorClass, vPos, rot, scale, id); }
	CActor* GetActor(uint32_t iEntityId) { return VirtualFunction<CActor* (__thiscall*)(void*, uint32_t)>(this, 0x78 / 8)(this, iEntityId); }
	bool IsNotMyTeam(CActor* lActor, CActor* pActor){ return ((lActor->GetTeamId() != pActor->GetTeamId() || pActor->GetTeamId() == 0) && (pActor != lActor)); }
	bool IsMyTeam(CActor* lActor, CActor* pActor) {return ((lActor->GetTeamId() == pActor->GetTeamId() && lActor != pActor)); }
	std::map<unsigned int, CActor*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, CActor*>>> GetActors() { return *(std::map<unsigned int, CActor*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, CActor*>>>*)((DWORD64)this + 0x30); }
};