#pragma once

class CInventory
{
public:
	void SetAmmoCount(CEntityClass* pAmmoType, int count) { VirtualFunction<void(__thiscall*)(void*, CEntityClass*, int)>(this, 464 / 8)(this, pAmmoType, count); }
	int GetAmmoCount(CEntityClass* pAmmoType) { return VirtualFunction <int(__thiscall*)(void*, CEntityClass*)>(this, 472 / 8)(this, pAmmoType); }
	int GetAmmoCapacity(CEntityClass* pAmmoType) { return VirtualFunction<int(__thiscall*)(void*, CEntityClass*)>(this, 488 / 8)(this, pAmmoType); }
};