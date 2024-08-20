#pragma once
#include "CWeaponParameters.h"
#include "CWeaponNetwork.h"

#include "CWeaponSettings.h"

#include "SGameClientHitInfo.h"

class CItemProxy;

class CItemBoxProxy
{
public:
	bool IsLocalClient() { return VirtualFunction<bool(__thiscall*)(void*)>(this, 576 / 8)(this); }
	bool IsClient() { return VirtualFunction<bool(__thiscall*)(void*)>(this, 568 / 8)(this); }
};

class CItemBox
{
public:
	char pad_0x0018[0x18];
	int owner_id;

	void SetOwnerId(EntityId pEntityId) { this->owner_id = pEntityId; }
	CItemBoxProxy* GetProxy() { return VirtualFunction<CItemBoxProxy*(__thiscall*)(void*)>(this, 32 / 8)(this); }
};


class CWeaponMaster
{
public:
	char pad_0x0000[0x5B0];
	int m_bIsRechargeable;
};
/*
using fnRequestShootHit = void(__fastcall*)(CGameObject*, void*, SRequestShootHit*, int, int);
fnRequestShootHit oRequestShoot;
void __fastcall RequestHits(CGameObject* pGameObject, void* pMethod, SRequestShootHit* pHits, int iCaller, int Channel)
{
	
	if (PussySettings::DamageWeapon)
	{
		if (!pHits->shoots.empty())
		{
			for (auto hits = pHits->shoots.begin(); hits != pHits->shoots.end(); hits++)
			{
				if (!hits->hits.empty())
				{
					for (auto it = hits->hits.begin(); it != hits->hits.end(); it++)
					{
						for (int i = 0; i < PussySettings::Damage; i++)
						{
							hits->hits.push_back(SNetHitInfo(it->targetId, it->material, it->typeId, it->partId, it->pos, it->damageReduction, it->profilerId));
						}
					}

					pHits->shoots.push_back(SShootInfo(hits->projectileId, hits->hits));
				}
			}
		}
		
		if (!pHits->shoots.empty())
		{
			oRequestShoot(pGameObject, pMethod, pHits, iCaller, Channel);
		}
	}
	else
	{
		oRequestShoot(pGameObject, pMethod, pHits, iCaller, Channel);
	}

	if (PussySettings::Headshot)
	{
		if (!pHits->shoots.empty())
		{
			for (auto hits = pHits->shoots.begin(); hits != pHits->shoots.end(); hits++)
			{
				if (!hits->hits.empty())
				{
					for (auto it = hits->hits.begin(); it != hits->hits.end(); it++)
					{
						//for (int i = 0; i < PussySettings::Damage; i++)
						//{
						hits->hits.push_back(SNetHitInfo(it->targetId, 1, it->typeId, it->partId, it->pos, it->damageReduction, it->profilerId));
						//}
					}

					pHits->shoots.push_back(SShootInfo(hits->projectileId, hits->hits));
				}
			}
		}

		if (!pHits->shoots.empty())
		{
			oRequestShoot(pGameObject, pMethod, pHits, iCaller, Channel);
		}
	}
	
	if(!PussySettings::Headshot && !PussySettings::DamageWeapon)
	{
		oRequestShoot(pGameObject, pMethod, pHits, iCaller, Channel);
	}
}
*/
struct DefibrillatorParams
{
	unsigned int targetId;
	unsigned int projId;
	bool resurrect;
	unsigned int cmdN;
};

struct RestoreParams
{
	bool useOnYourself;
	bool startingRestore;
	unsigned int healId;
	unsigned int teamMateId;
};


enum ERestoringType
{
	SelfRestoring = 0x0,
	TeammateRestoring = 0x1,
};

class CWeaponGeneral
{
private:
	CWeaponNetwork** GetWeaponNetwork() { return *(CWeaponNetwork***)((DWORD64)this + 0xB0); }
	CWeaponNetwork* GetNetwork() { return *(CWeaponNetwork**)((DWORD64)this + 0xB0); }
public:
	enum class EWeaponStates {

		eWS_Disabled = 0,
		eWS_Idle = 1,
		eWS_IdleZoomed = 2,
		eWS_Fire = 3,
		eWS_IdleUnderBarrel = 4,
		eWS_oldFireUnderBarrel = 5,
		eWS_FireUnderBarrel = 6,
		eWS_ReloadUnderBarrel = 7,
		eWS_olsterInDisabled = 8,
		eWS_olsterInUnderBarrel = 9,
		eWS_olsteredUnderBarrel = 0x0A,
		eWS_MeleeUnderBarrel = 0x0B,
		eWS_TrowingFire = 0x0C,
		eWS_TrowingFireActivate = 0x0D,
		eWS_ZoomedFire = 0x0E,
		eWS_ZoomInFire = 0x0F,
		eWS_ZoomOutFire = 0x10,
		eWS_Reload = 0x11,
		eWS_ReloadBarrel = 0x12,
		eWS_BoltAction = 0x13,
		eWS_ZoomedBoltAction = 0x14,
		eWS_ZoomIn = 0x15,
		eWS_ZoomOut = 0x16,
		eWS_ZoomOutReloadAuto = 0x17,
		eWS_ZoomOutReloadManual = 0x18,
		eWS_ZoomOutQSA = 0x19,
		eWS_ZoomOutMelee = 0x1A,
		eWS_ZoomOutBoltAction = 0x1B,
		eWS_ZoomOutCustomize = 0x1C,
		eWS_Trowing = 0x1D,
		eWS_Toss = 0x1E,
		eWS_Melee = 0x1F,
		eWS_Select = 0x20,
		eWS_Deselect = 0x21,
		eWS_olding = 0x22,
		eWS_Activate = 0x23,
		eWS_Customize = 0x24,
		eWS_CustomizeIn = 0x25,
		eWS_CustomizeOut = 0x26,
		eWS_olsterIn = 0x27,
		eWS_olstered = 0x28,
		eWS_StartRestoreSelf = 0x29,
		eWS_StartRestoreTeamMate = 0x2A,
		eWS_CancelRestore = 0x2B,
		eWS_RestoreSelf = 0x2C,
		eWS_RestoreTeamMate = 0x2D,
		eWS_TryingRestoreSelf = 0x2E,
		eWS_TryingRestoreTeamMate = 0x2F,
		eWS_DropAmmoPack = 0x30,
		eWS_Resurrect = 0x31,
		eWS_ResetClipAmmo = 0x32,
		eWS_Last = 0x33,
		eWS_Num = 0x33
	};

	using SvRequestShoot = void(__fastcall*)(CGameObject*, void*, SGameClientHitInfo*, int, int);
	using fnRequestShoot = void(__fastcall*)(CGameObject*, void*, SServerHitInfo*, int, int);
	using fnRequestHit = void(__fastcall*)(CGameObject*, void*, SvRequestHitParams*, int, int);
	using fnRequestShootHit = void(__fastcall*)(CGameObject*, void*, SRequestShootHit*, int, int);
	using fnUseDefibrillator = void(__fastcall*)(CGameObject*, void*, SRequestShootHit*, int, int);
	using fnSetChargeLevel = void(__fastcall*)(CWeaponGeneral*, int);
	using fnStartRestore = void(__fastcall*)(CWeaponNetwork*, ERestoringType);
	using fnStartRestoreSelf = void(__fastcall*)(CWeaponNetwork*, bool, bool, EntityId, bool);

	CItemProxy* GetItemProxy() { return *(CItemProxy**)((uint64_t)this + 0x38); }
	CGameObject* GetGameObject() { return VirtualFunction<CGameObject* (__thiscall*)(void*)>(this, 0x40 / 8)(this); } //return *(CGameObject**)((uint64_t)this + 0x38); }
	CWeaponMaster* GetWeaponMaster() { return *(CWeaponMaster**)((uint64_t)this + 0x8); }
	//CWeaponSettings* GetWeaponSettings() { return *(CWeaponSettings**)((uint64_t)this + 0x60); }
	CWeaponParameters* GetWeaponParameters() { return VirtualFunction<CWeaponParameters*(__thiscall*)(void*)>(this, 0x10 / 8)(this); }
	EWeaponStates GetWeaponState() { return VirtualFunction<EWeaponStates(__thiscall*)(void*)>(this, 0x28 / 8)(this); }
	CItemBox* GetItemBox() { return VirtualFunction<CItemBox*(__thiscall*)(void*)>(this, 32 / 8)(this); }
	bool IsZoomed() { return this->GetWeaponState() == EWeaponStates::eWS_IdleZoomed; }
	bool IsZoomIn() { return this->GetWeaponState() == EWeaponStates::eWS_ZoomIn; }
	bool IsZoomedFire() { return this->GetWeaponState() == EWeaponStates::eWS_ZoomedFire; }
	bool IsZoomedInFire() { return this->GetWeaponState() == EWeaponStates::eWS_ZoomInFire; }
	bool IsZoomedOut() { return this->GetWeaponState() == EWeaponStates::eWS_ZoomOut; }
	bool IsFullZoomed() {
		return this->GetWeaponState() == EWeaponStates::eWS_ZoomOut || this->GetWeaponState() == EWeaponStates::eWS_IdleZoomed || this->GetWeaponState() == EWeaponStates::eWS_ZoomedBoltAction ||
			this->GetWeaponState() == EWeaponStates::eWS_ZoomedFire || this->GetWeaponState() == EWeaponStates::eWS_ZoomIn || this->GetWeaponState() == EWeaponStates::eWS_ZoomInFire;
	}
	bool IsFiring() { return this->GetWeaponState() == EWeaponStates::eWS_Fire || this->GetWeaponState() == EWeaponStates::eWS_FireUnderBarrel || this->GetWeaponState() == EWeaponStates::eWS_oldFireUnderBarrel || this->GetWeaponState() == EWeaponStates::eWS_ZoomedFire || this->m_pWeaponState == EWeaponStates::eWS_ZoomInFire || this->m_pWeaponState == EWeaponStates::eWS_ZoomOutFire || this->m_pWeaponState == EWeaponStates::eWS_TrowingFire; }
	bool IsReloading() { return this->GetWeaponState() == EWeaponStates::eWS_Reload || this->GetWeaponState() == EWeaponStates::eWS_ReloadBarrel || this->GetWeaponState() == EWeaponStates::eWS_ReloadUnderBarrel;  }
	// E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? B0 01 48 8B BC 24 ? ? ? ? 48 8B B4 24 ? ? ? ? 48 81 C4 ? ? ? ?
	void SvRequestUseDefibrillator(EntityId trgId) { ((void(__thiscall*)(CWeaponGeneral*, EntityId, bool))0x1414D1050)(this, trgId, true); }
	void SvRequestStartRestore(ERestoringType type) { fnStartRestore(0x1413D9600)(this->GetNetwork(), type); }
	void SvRequestRestoreSelf(EntityId id) { fnStartRestoreSelf(0x1413D9890)(this->GetNetwork(), true, true, id, false); }
	void RequestShootHit(SGameClientHitInfo* HitInfo) { ((void(__thiscall*)(CWeaponGeneral*, SGameClientHitInfo*))0x14146D600)(this, HitInfo); }
	void ClRequestShootHit() { ((void(__thiscall*)(CWeaponGeneral*))0x14146D600)(this); }
	void RequestHit(CGameObject* pGameObject, SRequestShootHit pHitInfo) { fnRequestShootHit(SvRequestShootHit/*function*/)(pGameObject, *reinterpret_cast <void**>(OffRequestShootHit)/*allocator*/, &pHitInfo, 0x100, 0xFFFFFFFF); }
	void RequestShootHit(CGameObject* pGameObject, SGameClientHitInfo pHitInfo) { SvRequestShoot(SvRequestShootHit/*function*/)(pGameObject, *reinterpret_cast <void**>(OffRequestShootHit)/*allocator*/, &pHitInfo, 0x100, 0xFFFFFFFF); }
	void SvRequestReload(bool bAction = false) { ((void(__fastcall*)(PVOID64, bool))0x1415389E0)(this->GetWeaponNetwork(), bAction); } // sub_14138AAA0 | lea rdx, aAuto; "auto" | lea rax, aManual; "manual" -> upper SSGE
	CWeaponSettings* GetWeaponSettings() { return *(CWeaponSettings**)((__int64)this + 0x68);}
	const char* GetName() { return this->Get<CryStringT>(0x28).m_str; }

	template <class T> inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }
	template <class T> inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }
	void SetShootCount(int count) { Set<int>(0x120, count); } //Set<int>(0x124, count); }
	int GetShootCount() { return Get<int>(120); }
private:
	char pad_0x0000[0xB8]; //0x0000
	EWeaponStates m_pWeaponState; // 0xB8
};