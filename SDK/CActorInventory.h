#pragma once
#include <vector>

enum EProfileItemType
{
	ePIT_None = 0x0,
	ePIT_Weapon = 0x1,
	ePIT_Attachment = 0x2,
	ePIT_Armor = 0x3,
	ePIT_FragGrenade = 0x4,
	ePIT_FlashGrenade = 0x5,
	ePIT_SmokeGrenade = 0x6,
	ePIT_Claymore = 0x7,
	ePIT_Medkit = 0x8,
	ePIT_ArmorKit = 0x9,
	ePIT_Defibrillator = 0xA,
	ePIT_Decal = 0xB,
	ePIT_AmmoPack = 0xC,
	ePIT_Booster = 0xD,
	ePIT_ClanToken = 0xE,
	ePIT_Coin = 0xF,
	ePIT_Contract = 0x10,
	ePIT_MissionAccess = 0x11,
	ePIT_Key = 0x12,
	ePIT_TopPrizeToken = 0x13,
	ePIT_MetaGame = 0x14,
	ePIT_Bundle = 0x15,
	ePIT_WeaponSkin = 0x16,
	ePIT_Count = 0x17,
};

struct CSlotSet
{
	bool m_modified;
	char m_slotForClass[5];
};

struct SProfileItem
{
	int id;
	CryStringT name;
	int classes;
	CSlotSet slotSet;
	int amount;
	int attached_to;
	int displayMode;
	CryStringT material;
	CryStringT ui_name;
	CryStringT description;
	CryStringT icon;
	CryStringT category;
	CryStringT rarity;
	unsigned __int64 equippedTimeUtc;
	unsigned __int64 buyTimeUtc;
	unsigned __int64 expirationTimeUtc;
	unsigned int secondsLeft;
	DWORD64 timeWhenLoaded;
	bool expiredAndConfirmed;
	int totalDurabilityPoints;
	int durabilityPoints;
	int repairCost;
	unsigned __int16 quantity;
	bool permanent;
	bool isDefault;
	CryStringT decal_config[5];
	EProfileItemType itype;
	bool root;
	CryStringT root_name;
	int root_id;
	bool isModified;
};

class CActorInventory;

struct SWCategory
{
	CryStringT name;
	int multiple;
	std::vector<enum ECharacterClassId, std::allocator<enum ECharacterClassId> > classes;
};

const struct SWSlot
{
	CryStringT name;
	CryStringT action;
	int priority;
	std::vector<SWCategory, std::allocator<SWCategory> > categories;
};

struct CSlotWeapon
{
	int m_weaponId;
	CWeaponGeneral* m_pWeapon;
};

struct CInventoryWeaponSlot
{
	CSlotWeapon m_slotWeapons[5];
	SWSlot* m_slotConfig;
};

class CActorInventory
{
private:
	using fSpawnItem = CItemProxy * (__fastcall*)(CActorInventory*, const char*, int, const char*, const char*);
	using fPickAmmo = void(__fastcall*)(CActorInventory*, const char*, int);
	using fPickUp = void(__fastcall*)(CActorInventory*, unsigned int, int);
	using fChangeWeaponTo = bool(__fastcall*)(CActorInventory*, CWeaponGeneral*);
	using fSetCurrWeapon = void(__fastcall*)(CActorInventory*, CWeaponGeneral*);
	using fSelectItem = void(__fastcall*)(CActorInventory*, unsigned int);
public:
	//sub_14130EAE0
	char pad_0x0078[0xC0]; // ClPickUp
	std::map<CryStringT, CInventoryWeaponSlot, std::less<CryStringT >, std::allocator<std::pair<CryStringT const, CInventoryWeaponSlot> > > m_weaponSlots;
	// E8 ? ? ? ? 48 8B D8 48 85 C0 74 3A 48 8B C8 E8 ? ? ? ? 84 C0 74 2E 48 8B CD
	CItemProxy* SpawnItem(const char* className, int id, const char* displayName, const char* shopName) { return fSpawnItem(0x14133C200)(this, className, id, displayName, shopName); }
	void SetCurrWeapon(CWeaponGeneral* pWeapon) { fSetCurrWeapon(0x1413340B0)(this, pWeapon); } // hideout_custom
	void SelectItem(EntityId id) { fSelectItem(0x1413351A0)(this, id); } // pocket_frag_grenade
	CWeaponGeneral* GetMeleeWeapon() 
	{
		for (auto it = this->m_weaponSlots.begin(); it != this->m_weaponSlots.end(); it++)
		{
			if (strstr(it->first.m_str, "knife"))
			{
				return it->second.m_slotWeapons[0].m_pWeapon;
			}
		}
	}

	CWeaponGeneral* GetPistolWeapon()
	{
		for (auto it = this->m_weaponSlots.begin(); it != this->m_weaponSlots.end(); it++)
		{
			if (strstr(it->first.m_str, "pistol"))
			{
				return it->second.m_slotWeapons[0].m_pWeapon;
			}
		}
	}

	CWeaponGeneral* GetMainWeapon()
	{
		for (auto it = this->m_weaponSlots.begin(); it != this->m_weaponSlots.end(); it++)
		{
			if (strstr(it->first.m_str, "primary"))
			{
				return it->second.m_slotWeapons[0].m_pWeapon;
			}
		}
	}

	CWeaponGeneral* GetHealWeapon(int actClass)
	{
		for (auto it = this->m_weaponSlots.begin(); it != this->m_weaponSlots.end(); it++)
		{
			//for (int i = 0; i <= 4; i++)
			//{
			if (actClass == Medic)
			{
				if (strstr(it->second.m_slotWeapons[0].m_pWeapon->GetName(), "mk01"))
				{
					return it->second.m_slotWeapons[0].m_pWeapon;
				}
			}
			else if (actClass == Engineer)
			{
				if (strstr(it->second.m_slotWeapons[0].m_pWeapon->GetName(), "ak01"))
				{
					return it->second.m_slotWeapons[0].m_pWeapon;
				}
			}
			//}
		}
	}


	void DebugWeapons()
	{
		for (auto it = this->m_weaponSlots.begin(); it != this->m_weaponSlots.end(); it++)
		{
			std::cout << it->first.m_str << std::endl;
			if (it->second.m_slotWeapons[0].m_pWeapon != nullptr)
			{
				std::cout << "[" << 0 << "] " << it->second.m_slotWeapons[0].m_pWeapon->GetName() << std::endl;
			}
		}
	}


	//int FillInventory(std::vector<SProfileItem>* inventory, bool bAmmoInClip) { return fnFillInventory(0x14130EAE0)(this, inventory, bAmmoInClip); }
	//int SpawnItem(const char* className, int id, const char* displayName, const char* shopName) { return fnSpawnItem(0x141313620)(this, className, id, displayName, shopName); } // OnUpdateItems

};