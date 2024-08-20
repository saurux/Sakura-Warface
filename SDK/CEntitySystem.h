#pragma once

#include "CEntityIterator.h"

class CEntityArchetype
{
public:

};

class IEntitySpawnParams
{
public:
	EntityId Id; //0x0000 
	char pad_0x0004[0x14]; //0x0004 
	CEntityClass* pClass; //0x0018 
	CEntityArchetype* pArchetype;
	char pad_0x0020[0x8]; //0x0020 
	const char* sName; //0x0030 
	char pad_0x0038[0x8]; //0x0038 
	DWORD nFlags; //0x0040 
	char pad_0x0044[0x3]; //0x0044 
	Vec3 vPosition; //0x0047 
	Quat qRotation; //0x0053 
	Vec3 vScale; //0x0063 
	char pad_0x00060[0x90];
}; //Size=0x0068

class CEntityClassRegistry
{
public:
	CEntityClass* FindClass(const char* sClassName)
	{
		return VirtualFunction<CEntityClass* (__thiscall*)(void*, const char*)>(this, 24 / 8)(this, sClassName);
	}
};

class CEntitySystem
{
public:
	// 0x140
	char pad_0x0140[0x140];
	std::multimap<const char*, unsigned int> m_mapEntityNames;
	CEntity* SpawnEntity(IEntitySpawnParams& params, bool bAutoInit = true) {return VirtualFunction<CEntity* (__thiscall*)(void*, IEntitySpawnParams&, bool)>(this, 72 / 8)(this, params, bAutoInit);}
	CEntityIterator* GetEntityIterator() { return VirtualFunction<CEntityIterator* (__thiscall*)(void*)>(this, 168 / 8)(this); }
	CEntity* GetEntity(EntityId pEntityId) { return VirtualFunction<CEntity* (__thiscall*)(void*, EntityId)>(this, 88 / 8)(this, pEntityId); } // "RMI onClient or otherClients must have a valid channel id for its first argument"
	CEntityClassRegistry* GetClassRegistry() { return VirtualFunction<CEntityClassRegistry* (__thiscall*)(void*)>(this, 64 / 8)(this); }
	CEntity* FindEntityByName(const char* name) { return VirtualFunction<CEntity* (__thiscall*)(void*, const char*)>(this, 96 / 8)(this, name); }
	void RemoveEntity(EntityId entity, bool bForceRemoveNow) { VirtualFunction<void (__thiscall*)(void*, EntityId, bool)>(this, 0x80 / 8)(this, entity, bForceRemoveNow); }
	CEntity* GetEntityFromPhysics(IPhysicalEntity* pEntity) { return VirtualFunction<CEntity* (__thiscall*)(void*, IPhysicalEntity*)>(this, 208 / 8)(this, pEntity); }
	CEntity* SpawnObject(const char* entityName, const char* entityClass, Vec3 vPos)
	{
		if (CEntityClass* pClass = this->GetClassRegistry()->FindClass(entityClass))
		{
			IEntitySpawnParams spawnParams;
			memset(&spawnParams, 0, sizeof(IEntitySpawnParams));
			spawnParams.vPosition = vPos;
			spawnParams.sName = entityName;
			spawnParams.pClass = pClass;
			spawnParams.qRotation.w = 1.f;
			spawnParams.vScale = Vec3(1.f, 1.f, 1.f);
			return this->SpawnEntity(spawnParams);
		}
		return NULL;
	}
};