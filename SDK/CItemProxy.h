#pragma once

#include "CEntity.h"
#include "CWeapon.h"

const struct SProjectileLaunchParams
{
	float fSpeedScale;
	unsigned int trackingId;
	Vec3 vShootTargetPos;
};

class CItemView
{
public:

};

class CItemProxy
{
private:
	char pad_0x0000[0x10];			//0x0000
	CEntity* m_pEntity;				//0x0010
	uint32_t m_entityId;			//0x0020
	char pad_0x0024[0x28];			//0x0024
	uint32_t m_dwItemId;			//0x004C
public:
	CGameObject* GetGameObject() { return  *(CGameObject**)((uintptr_t)this + 0x18); }
	CWeapon* GetWeapon() { return VirtualFunction<CWeapon* (__thiscall*)(void*)>(this, 632 / 8)(this); }
	CEntity* GetWeaponEntity() { return this->m_pEntity; }
	EntityId GetCurrentItemId() {return this->m_dwItemId;}
	CWeaponGeneral* GetWeaponGeneral() { return  *(CWeaponGeneral**)((uintptr_t)this + 0x30); }
	CItemView* GetItemView() { return  *(CItemView**)((uintptr_t)this + 0x38); }
	CItemBox* GetItemBox() { return VirtualFunction<CItemBox* (__thiscall*)(void*)>(this, 968 / 8)(this);}
	void StartFire(SProjectileLaunchParams* params) { VirtualFunction<void(__thiscall*)(void*, SProjectileLaunchParams*)>(this, 80 / 8)(this, params); }
};