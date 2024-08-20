#pragma once

#include "CActorInventory.h"

enum ECharacterClassId
{
	eCCI_First = 0x0,
	eCCI_Rifleman = 0x0,
	eCCI_Heavy = 0x1,
	eCCI_Recon = 0x2,
	eCCI_Medic = 0x3,
	eCCI_Engineer = 0x4,
	eCCI_Count = 0x5,
	eCCI_Other = 0xFFFFFFFF,
};

enum EGender
{
	GENDER_MALE = 0x0,
	GENDER_FEMALE = 0x1,
	SerGENDER_FIRST = 0x0,
	SerGENDER_LAST = 0x1,
	SerGENDER_UNKNOWN = 0x2,
};

template <typename T>
struct SVarOptional
{
	T m_var;
	bool m_initialized;
};

template <typename T>
struct SVarTrack
{
	SVarOptional<T> m_var;
	bool m_changed;
};


struct SPlayerBanner
{
	int achievements[3];
};

struct SUserMoney
{
	int gameMoney;
	int cryMoney;
	int crownMoney;
	const char* keyItemName;
};

struct CPvpRatingState 
{
	int m_rank;
	int m_previousRank;
	int m_winStreakBonus;
	const char* m_progress;
	const char* m_gamesHistory;
	const char* m_previousGamesHistory;
};

struct SACharacterInfo {

	const char* head; //0x0000 
	char pad_0x0008[0x8]; //0x0008
	const char* nickname; //0x0010 
	char pad_0x0018[0x8]; //0x0018
	float height; //0x0020 
	__int32 fatness; //0x0024 
	__int32 gender; //0x0028 
	char pad_0x002C[0x4]; //0x002C
	SUserMoney profileMoney; //0x0030 
	__int32 experience; //0x0050 
	__int32 initialExperience; //0x0054 
	CPvpRatingState pvpRatingState; //0x0058 
	__int32 currentClass; //0x0098 
	char pad_0x009C[0x8]; //0x009C
	SPlayerBanner banner; //0x00A4 

}; //Size=0x00B0

struct SProfileItemA
{
	int id;
	const char* name;
	int classes;
	CSlotSet slotSet;
	int amount;
	int attached_to;
	int displayMode;
	const char* material;
	const char* ui_name;
	const char* description;
	const char* icon;
	const char* category;
	const char* rarity;
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
	const char* decal_config[5];
	EProfileItemType itype;
	bool root;
	const char* root_name;
	int root_id;
	bool isModified;
};

class CProfileItems;

using fnAddItem = int(__stdcall*)(CProfileItems*, SProfileItem);
fnAddItem oAddItem = nullptr;

int __stdcall hkAddItem(CProfileItems* pProfileItems, SProfileItem item)
{
	std::cout << item.name.m_str << std::endl;

	return oAddItem(pProfileItems, item);
}

class CProfileItems
{
public:
	//using fnAddItem = int(__fastcall*)(CProfileItems*, SProfileItem);
	using fnGetItems = void(__fastcall*)(CProfileItems*, EProfileItemType, ECharacterClassId, std::vector<SProfileItem>*);

	int AddItem(SProfileItem item) { return fnAddItem(0x141433140)(this, item); }
	void GetItems(EProfileItemType itype, ECharacterClassId classId, std::vector<SProfileItem>* result) { fnGetItems(0x1414335B0)(this, itype, classId, result); } // hideout_custom

	char pad_0x0008[0x8];
	std::vector<SProfileItem, std::allocator<SProfileItem>> m_items;
	std::vector<unsigned __int64, std::allocator<unsigned __int64>> m_unlockedItems;
};

class COnlineProfile;

using fnAddMoney = int(__stdcall*)(COnlineProfile*, __int64, int);
fnAddMoney oAddMoney = nullptr;
using fnAddExperience = int(__stdcall*)(COnlineProfile*, int);
fnAddExperience oAddExperience = nullptr;

int __stdcall hkAddMoney(COnlineProfile* profile, __int64 currency, int money)
{
	money += 500000;
	return oAddMoney(profile, currency, money);
}

int __stdcall hkAddExperience(COnlineProfile* profile, int exp)
{
	exp += 500000;
	return oAddExperience(profile, exp);
}

struct SCharacterInfo
{
	CryStringT head;
	CryStringT nickname;
	float height;
	float fatness;
	EGender gender;
	SUserMoney profileMoney;
	int experience;
	int initialExperience;
	CPvpRatingState pvpRatingState;
	SVarTrack<enum ECharacterClassId> currentClass;
	SPlayerBanner banner;
};

class COnlineChannel;
using pPostSwitchChannel = void(__fastcall*)(COnlineProfile*, COnlineChannel*, EOnlineError, int);
pPostSwitchChannel oPostSwitchChannel;
void hkPostSwitchChannel(COnlineProfile* profile, COnlineChannel* channel, EOnlineError error, int code) {
	error = EOnlineError::eOnlineError_NoError;
	code = 0;
	return oPostSwitchChannel(profile, channel, error, code);
}

class COnlineProfile
{
private:

	//char pad_0x0514[0x514];
	//int achievements[3];
public:
	char pad_0x0470[0x790];
	SCharacterInfo m_characterInfo;

	char pad_0x0520[0x520];
	//SCharacterInfo m_characterInfo;
	CProfileItems m_profileItems;

	// profileid 0x518
	
	using fnSendLogoutToCurrentChannel = void(__stdcall*)(COnlineProfile*);
	using fnUpdateMoney = int(__fastcall*)(COnlineProfile*, int);
	using fnUpdateExperience = int(__fastcall*)(COnlineProfile*, int);

	void OnLogout() { VirtualFunction<void(__fastcall*)(COnlineProfile*)>(this, 0x68 / 8)(this); }

	int AddMoney(__int64 currency, int money){return fnAddMoney(0x141474D00)(this, currency, money);} // deferred_rewards_notification
	int AddExperience(int exp) { return fnAddExperience(0x141474D80)(this, exp); } // deferred_rewards_notification

	int UpdateMoney(__int64 currency, int money) { return fnAddMoney(0x141468970)(this, currency, money); } // generic_flash_popup_show
	int UpdateExperience(int exp) { return fnAddExperience(0x141468A80)(this, exp); } // generic_flash_popup_show

	void SendLogoutToCurrentChannel() { return fnSendLogoutToCurrentChannel(0x141632430)(this); } // [Online profile] Failed to connect MasterServer %s [%s], reason '%s' code %d:%d"

	void InstallHook3() {
		oPostSwitchChannel = CreateHook<pPostSwitchChannel>(reinterpret_cast<void*>(0x1416154E0), hkPostSwitchChannel);
	}

	void SetNickname(const char* nickname) { this->m_characterInfo.nickname.m_str = nickname; }
	//void SetExperience(int experience) { this->m_characterInfo.experience = experience; this->m_characterInfo.initialExperience = experience; }
	void SetExperience(int exp) { *(int*)((uint64_t)this + 0x4C0) = exp; }
	void SetProfileId(int profile) { *(int*)((uint64_t)this + 0xA90) = profile; } // %USER%/online_profile.xml
	//CryStringT GetNickname() { return this->m_nickname; }
	//void SetBanner(int ach) { this->achievements = ach; }

	//SCharacterInfo GetCharacterInfo() { return *(SCharacterInfo*)((uint64_t)this + 0x470); }
	//SCharacterInfo* GetCharacterInfo() { return this->m_characterInfo; }
	CProfileItems GetProfileItems() { return *(CProfileItems*)((uint64_t)this + 0x520); } // [Online profile] Profile data successfully loaded
	CProfileItems* GetItems() { return &this->m_profileItems; }
	COnlineProfile* GetThis() { return this; }

	DWORD64 dwAddMoney = 0x141468B50;
};