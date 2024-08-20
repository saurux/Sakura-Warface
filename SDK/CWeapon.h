#pragma once

#include "CWeaponGeneral.h"

/*
struct IWeaponVtbl
{
	//virtual   void IWeaponVtbl(unsigned int id) = 0;
	char pad_0x0008[112];
	virtual   bool CanStopFire() = 0;
	virtual   void StartZoom(unsigned int id, int interval) = 0;
	virtual   void StopZoom(unsigned int id) = 0;
	virtual   bool CanZoom() = 0;
	virtual   void ExitZoom(bool manual) = 0;
	virtual   void Reload(bool manual) = 0;
	virtual   bool OutOfAmmo(bool manual) = 0;
	virtual   bool LowAmmo(float manual) = 0;
	virtual   int GetAmmoCount(CEntityClass* pEntityClass) = 0;
	virtual   void SetAmmoCount(CEntityClass* pEntityClass, int count) = 0;
	virtual   bool GetCrosshairVisibility() = 0;
	virtual   float GetCrosshairOpacity() = 0;
	virtual   int GetNumOfFireModes() = 0;
	virtual   CFireMode* GetFireMode(const char* name) = 0;
	virtual   CFireMode* GetFireMode(int index) = 0;
	virtual   int GetFireModeIdx(const char* name) = 0;
	virtual   int GetCurrentFireMode() = 0;
	virtual   void SetCurrentFireMode(const char* name) = 0;
	virtual   void SetCurrentFireMode(int index) = 0;
	virtual   void ChangeFireMode() = 0;
	virtual   struct IZoomMode* GetZoomMode(const char* name) = 0;
	virtual   struct IZoomMode* GetZoomMode(int index) = 0;
	virtual   int GetCurrentZoomMode() = 0;
	virtual   void SetCurrentZoomMode(const char* name) = 0;
	virtual   void SetCurrentZoomMode(int index) = 0;
	virtual   void SetHostId(unsigned int id) = 0;
	virtual   unsigned int GetHostId() = 0;
	virtual   void MeleeAttack(bool secondary) = 0;
	virtual   bool CanMeleeAttack() = 0;
	virtual   bool PerformThrow(struct SProjectileLaunchParams* launch, CActor* pActor) = 0;
	virtual   void SaveWeaponPosition() = 0;
	virtual   bool IsValidAssistTarget(CEntity* pEntity, CEntity* mEntity, bool) = 0;
	virtual   void SendMusicLogicEvent(struct EMusicLogicEvents events) = 0;
	virtual   bool PredictProjectileHit(struct SPredictHitResults* result, IPhysicalEntity* pEntity, Vec3_tpl<float>* pos, Vec3_tpl<float>* dir, Vec3_tpl<float>* vel, float dmg, float rpm, int shots) = 0;
	virtual   bool PredictProjectileHit(IPhysicalEntity* pEntity, Vec3_tpl<float>* pos, Vec3_tpl<float>* dir, Vec3_tpl<float>* vel, float dist, Vec3_tpl<float>* position, float* resultdist, Vec3_tpl<float>* direction, unsigned int* result, float dmg) = 0;
	virtual   bool IsZoomed() = 0;
	virtual   bool IsZoomingInOrOut() = 0;
	virtual   bool IsReloading(bool manual) = 0;
	virtual   struct EZoomState GetZoomState() = 0;
	virtual   bool GetScopePosition(Vec3_tpl<float>* result) = 0;
	virtual   bool HasAttachmentAtHelper(const char* name) = 0;
	virtual   void GetAttachmentsAtHelper(const char* name, struct CCryFixedStringListT* list) = 0;
	virtual   bool IsServerSpawn(CEntityClass* pEntityClass) = 0;
	virtual   struct AIWeaponDescriptor* GetAIWeaponDescriptor() = 0;
	virtual   bool Query(struct EWeaponQuery query, const void* handle) = 0;
	virtual   void RequestShoot(CEntityClass* pAmmoClass, Vec3_tpl<float>* pos, Vec3_tpl<float>* dir, Vec3_tpl<float>* vel, Vec3_tpl<float>* lev, float dmg, int look, bool b) = 0;
	virtual   struct IFireMode* GetMeleeFireMode() = 0;
	virtual   bool IsPendingFireRequest() = 0;
	virtual   bool IsSwitchingFireMode() = 0;
	virtual   void StartChangeFireMode() = 0;
	virtual   void EndChangeFireMode() = 0;
	virtual   void ExitViewmodes() = 0;
	virtual   struct IItem* GetIItem() = 0;
	virtual   void SendEndReload() = 0;
	virtual   bool IsTargetOn() = 0;
	virtual   void OnReadyToFire() = 0;
	virtual   void OnStartReload(unsigned int id, CEntityClass* pEntityClass) = 0;
	virtual   void OnEndReload(unsigned int id, CEntityClass* pEntityClass) = 0;
	virtual   void OnMelee(unsigned int id) = 0;
	virtual   void OnZoomIn() = 0;
	virtual   void OnZoomOut() = 0;
	virtual   void OnShoot(unsigned int m, unsigned int p, CEntityClass* pEntityClass, Vec3_tpl<float>* pos, Vec3_tpl<float>* dir, Vec3_tpl<float>* vel) = 0;
	virtual   void OnStartTargetting(IWeaponVtbl* pWeapon) = 0;
	virtual   void OnStopTargetting(IWeaponVtbl* pWeapon) = 0;
	virtual   void RequestLock(unsigned int id, int idx) = 0;
	virtual   void RequestUnlock() = 0;
	virtual   void RequestStartFire() = 0;
	virtual   void RequestStopFire() = 0;
	virtual   void RequestReload() = 0;
	virtual   void RequestCancelReload() = 0;
	virtual   void RequestStartMeleeAttack(bool, bool) = 0;
	virtual   void RequestMeleeAttack(bool secondary, Vec3_tpl<float>* playerPos, Vec3_tpl<float>* pos) = 0;
	virtual   void OnOutOfAmmo(CEntityClass* pAmmoClass) = 0;
	virtual   struct CProjectile* SpawnAmmo(CEntityClass* pAmmoClass, bool server) = 0;
	virtual   int GetInventoryAmmoCount(CEntityClass* pAmmoClass) = 0;
	virtual   void SetInventoryAmmoCount(CEntityClass* pAmmoClass, int count) = 0;
	virtual   int GetMaxZoomSteps() = 0;
	virtual   Vec3_tpl<float>* GetAimLocation() = 0;
	virtual   Vec3_tpl<float>* GetTargetLocation() = 0;
	virtual   void SetAimLocation(Vec3_tpl<float>* pos) = 0;
	virtual   void SetTargetLocation(Vec3_tpl<float>* pos) = 0;
	virtual   bool AIUseEyeOffset() = 0;
	virtual   bool AIUseOverrideOffset(enum EStance stance, float f, float f2, Vec3_tpl<float>* pos) = 0;
	virtual   void AutoDrop() = 0;
	virtual   void AddFiredRocket() = 0;
	virtual   bool GetFireAlternation() = 0;
	virtual   void SetFireAlternation(bool b) = 0;
	virtual   unsigned int GetHeldEntityId() = 0;
	virtual   void ActivateTarget(bool b) = 0;
	virtual   bool ApplyActorRecoil() = 0;
	virtual   bool IsRippedOff() = 0;

};
*/

enum EMusicLogicEvents : __int32
{
	eMUSICLOGICEVENT_SET_MULTIPLIER = 0x0,
	eMUSICLOGICEVENT_SET_AI_MULTIPLIER = 0x1,
	eMUSICLOGICEVENT_SET_AI = 0x2,
	eMUSICLOGICEVENT_CHANGE_AI = 0x3,
	eMUSICLOGICEVENT_SET_PLAYER = 0x4,
	eMUSICLOGICEVENT_CHANGE_PLAYER = 0x5,
	eMUSICLOGICEVENT_SET_GAME = 0x6,
	eMUSICLOGICEVENT_CHANGE_GAME = 0x7,
	eMUSICLOGICEVENT_SET_ALLOWCHANGE = 0x8,
	eMUSICLOGICEVENT_CHANGE_ALLOWCHANGE = 0x9,
	eMUSICLOGICEVENT_VEHICLE_ENTER = 0xA,
	eMUSICLOGICEVENT_VEHICLE_LEAVE = 0xB,
	eMUSICLOGICEVENT_WEAPON_MOUNT = 0xC,
	eMUSICLOGICEVENT_WEAPON_UNMOUNT = 0xD,
	eMUSICLOGICEVENT_SNIPERMODE_ENTER = 0xE,
	eMUSICLOGICEVENT_SNIPERMODE_LEAVE = 0xF,
	eMUSICLOGICEVENT_CLOAKMODE_ENTER = 0x10,
	eMUSICLOGICEVENT_CLOAKMODE_LEAVE = 0x11,
	eMUSICLOGICEVENT_ENEMY_SPOTTED = 0x12,
	eMUSICLOGICEVENT_ENEMY_KILLED = 0x13,
	eMUSICLOGICEVENT_ENEMY_HEADSHOT = 0x14,
	eMUSICLOGICEVENT_ENEMY_OVERRUN = 0x15,
	eMUSICLOGICEVENT_PLAYER_WOUNDED = 0x16,
	eMUSICLOGICEVENT_PLAYER_KILLED = 0x17,
	eMUSICLOGICEVENT_PLAYER_SPOTTED = 0x18,
	eMUSICLOGICEVENT_PLAYER_TURRET_ATTACK = 0x19,
	eMUSICLOGICEVENT_PLAYER_SWIM_ENTER = 0x1A,
	eMUSICLOGICEVENT_PLAYER_SWIM_LEAVE = 0x1B,
	eMUSICLOGICEVENT_EXPLOSION = 0x1C,
	eMUSICLOGICEVENT_FACTORY_CAPTURED = 0x1D,
	eMUSICLOGICEVENT_FACTORY_LOST = 0x1E,
	eMUSICLOGICEVENT_FACTORY_RECAPTURED = 0x1F,
	eMUSICLOGICEVENT_VEHICLE_CREATED = 0x20,
	eMUSICLOGICEVENT_MAX = 0x21,
};

class CWeapon
{
public:
	CWeapon* GetThis() { return this; }
	CWeaponGeneral* GetWeaponGeneral() { return (CWeaponGeneral*)*(DWORD64*)((DWORD64)this + 0x8); }
	void SetFirePosition(Vec3 vPos = ZERO) { *(Vec3*)((DWORD64) * (DWORD64*)((DWORD64)this + 0x18) + 0x1C) = vPos; }
	void StartFire() { VirtualFunction<void(__thiscall*)(void*)>(this, 88 / 8)(this); }
	void StopFire() { VirtualFunction<void(__thiscall*)(void*)>(this, 96 / 8)(this); }
	void RequestStartFire() { VirtualFunction<void(__thiscall*)(void*)>(this, 0x280 / 8)(this); }
	void RequestStopFire() { VirtualFunction<void(__thiscall*)(void*)>(this, 0x288 / 8)(this); }
	//CFireMode* GetFireMode(int idx) { return VirtualFunction<CFireMode* (__thiscall*)(void*, int)>(this, 224 / 8)(this, idx); }
	int GetCurrentFireMode() { return VirtualFunction<int(__thiscall*)(void*)>(this, 248 / 8)(this); }
	int GetAmmoCount() { return VirtualFunction<int(__thiscall*)(PVOID)>(this, 472 / 8)(this); }
	void SetAmmoCount(int Ammo) { VirtualFunction<void(__thiscall*)(PVOID, int)>(this, 464 / 8)(this, Ammo); }
	bool IsFiring() { return VirtualFunction<bool(__thiscall*)(PVOID)>(this, 208 / 8)(this);}
	int GetClipSize() { return VirtualFunction<bool(__thiscall*)(PVOID)>(this, 240 / 8)(this); }
	void MeleeAttack(bool bShort = true) { VirtualFunction<void(__thiscall*)(void*, bool)>(this, 0x148 / 8)(this, bShort); }
	void SendMusicLogicEvent(EMusicLogicEvents events) { VirtualFunction<void(__thiscall*)(void*, EMusicLogicEvents)>(this, 0x170 / 8)(this, events); }
	void RequestMeleeAttack(bool secondary, Vec3_tpl<float>* playerPos, Vec3_tpl<float>* pos) { VirtualFunction<void(__thiscall*)(void*, bool, Vec3_tpl<float>*, Vec3_tpl<float>*)>(this, 0x170 / 8)(this, secondary, playerPos, pos); } // 0x2A8
	void RequestShoot(CEntityClass* pAmmoType, const Vec3& pos, const Vec3& dir, const Vec3& vel, const Vec3& hit, float extra, int predictionHandle, bool forceExtended) { VirtualFunction<void(__thiscall*)(void*, CEntityClass*, const Vec3&, const Vec3&, const Vec3&, const Vec3&, float, int, bool)>(this, 480 / 8)(this, pAmmoType, pos, dir, vel, hit, extra, predictionHandle, forceExtended); }//480
	void* SpawnAmmo(CEntityClass* pAmmoType, bool remote = false) { return VirtualFunction<void*(__thiscall*)(void*, CEntityClass*, bool)>(this, 704 / 8)(this, pAmmoType, remote); }
	void SetInventoryAmmoCount(CEntityClass* pAmmoType, int count) { VirtualFunction<void(__thiscall*)(void*, CEntityClass*, int)>(this, 720 / 8)(this, pAmmoType, count); }
	void SetAimLocation(Vec3 location) { VirtualFunction<void(__thiscall*)(void*, Vec3)>(this, 752 / 8)(this, location); }
};