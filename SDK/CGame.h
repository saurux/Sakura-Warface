#pragma once
#pragma comment(lib, "Zydis.lib")
#pragma comment(lib, "HookLib.lib")

#include <Hook/HookLib/HookLib.h>

#include "CGameFramework.h"
#include "COnlineAccount.h"
#include "CGameRoom.h"

#include <Windows.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
#include <map>

class SCVars
{
public:
	template <class T>
	inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }

	template <class T>
	inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }
};

class CFlowchartManager;
class CFlowchartStateHandler;

enum EFlowchartState
{
	eFS_None = 0xFFFFFFFF,
	eFS_First = 0x0,
	eFS_NoUI = 0x0,
	eFS_Login = 0x1,
	eFS_LoadingLobby = 0x2,
	eFS_CharacterCreation = 0x3,
	eFS_Lobby = 0x4,
	eFS_LoadingLevel = 0x5,
	eFS_Ingame = 0x6,
	eFS_Renaming = 0x7,
	eFS_PromoTutorial = 0x8,
	eFS_PostGame = 0x9,
	eFS_Count = 0xA,
};

class CFlowchartStateHandler
{
public:
	char pad_0x01DC[0x1DC];
	bool bConnection;
};

class CTutorialStarter
{
public:
	//sub_14142BF60// @propose_tutorial
	using fnStartTutorial = void(__fastcall*)(CTutorialStarter*, unsigned int, bool);
	void StartTutorial(unsigned int tutorialId, bool force) { fnStartTutorial(0x141436BF0)(this, tutorialId, force); }
};

class ILoginProviderData {
public:
	const char* GetOnlineId() { return VirtualFunction<const char*(__thiscall*)(void*)>(this, 2)(this); }
	const char* GetPassword() { return VirtualFunction<const char*(__thiscall*)(void*)>(this, 3)(this); }
};

class CFlowchartManager
{
public:
	char pad_0000[0x30]; //0x0000
	EFlowchartState m_currentState; //0x0030
	bool bUnknown; //0x0034
	bool m_isStateChanging; //0x0035

	char pad_0x0060[0x60];
	CFlowchartStateHandler* m_graph[10];

	using fnSpawnAction = void(__stdcall*)(CFlowchartManager*, const char*);
	using fnStartLobby = void(__stdcall*)(CFlowchartManager*);
	using fnGotoState = void(__stdcall*)(CFlowchartManager*, EFlowchartState);
	void SpawnAction(const char* action) { fnSpawnAction(0x1410C3D50)(this, action); }
	void StartLobby() { return fnStartLobby(0x1410CC7C0)(this); } // close_map_voting
	void GotoState(EFlowchartState state) { return fnGotoState(0x141216C20)(this, state); } 
	void StartLobbyDeffered() { return fnStartLobby(0x1410CDED0)(this); } // CFlowchartManager::StartLobbyDeffere
	CTutorialStarter* GetTutorialStarter() { return *(CTutorialStarter**)(this + 0xD8); }
	ILoginProviderData* GetLoginProviderData() { return *(ILoginProviderData**)(this + 0xE0); }
	CFlowchartStateHandler* GetFlowchartStateHandler() { return this->m_graph[0]; }

	//_1410C3FA0
};

struct SAnimSelection
{
	float upperOffset;
	float upperOffset2;
	float middleOffset;
};

struct SClimbAnim
{
	CryStringV inputId;
	float length;
	float duration;
	float offsetFromTop;
	float playbackMult;
	CryStringV animName;
};

struct SClimbParams
{
	char pad_0x0010[0x10];
	float minHelperHeight;
	float maxHelperHeight;
	float detectZoneLength;
	float nearZoneLength;
	float lowerAnimStartDist;
	float verticalVelocity;
	SAnimSelection animSelection;
	SClimbAnim animations[4];
};

struct SSlideParams
{
	char pad_0x0010[0x10];
	float initialStaminaDrop;
	float staminaCost;
	float minHasteTimeBeforeSlide;
	float minSlidingTime;
	float slideInTime;
	float slideInFastTime;
	float slideFromJumpDelay;
	float horzLimitAngle;
	float vertLimitAngle;
	float viewOffsetZ;
	float slideOutVelocity;
	float speedIncreaseCoeff;
	float speed0;
	float time0;
	float speed1;
	float time1;
	float speed2;
	float time2;
	float speed3;
};

class CClimbClassExtension
{
public:
	char pad_0x0008[0x8];
	SClimbParams m_params;
};

class CSlidePersistent
{
public:
	char pad_0x0008[0x8];
	SSlideParams m_params;
};

struct SKnockBackParams
{
	char pad_0x0000[0x10];
	float horzLimitAnlge;
	float vertLimitAngleMin;
	float vertLimitAngleMax;
	float fallingTime;
	float raisingTimeSingle;
	float raisingTimeCoop;
	float cameraYawOffset;
	float cameraPitchOffset;
	float cameraRoll;
	Vec3 viewOffset;
	float stunDuration;
};

class CKnockBackPersistent
{
public:
	char pad_0x0000[0x8];
	SKnockBackParams m_params;
};

struct SRaiseAssistParams
{
	float assistTime;
};

struct CRaiseAssistPersistent
{
	SRaiseAssistParams m_params;
};

struct SVaultAnim
{
	CryStringT inputId;
	float offsetFromTop;
	CryStringT animName;
};

struct SVaultParams
{
	char pad_0x0000[0x10];
	float detectZoneLength;
	float nearZoneLength;
	float lowerAnimStartDist;
	float verticalVelocity;
	float animSelectionOffset;
	float animLength;
	float animTime;
	float animPlaybackMult;
	float minHelperHeight;
	float maxHelperWidth;
	float groundCheckStartTime;
	float lastSegmentLength;
	float groundMinDist;
	float trajectoryValidationPercent;
	SVaultAnim animations[2];
};

struct CVaultClassExtension
{
	SVaultParams m_params;
};

struct SCoopCinematicParams
{
	float fLocatorRadius;
	float fLocatorViewLimit;
	float fHorzLimitAngle;
	float fVertLimitAngle;
	CryStringT messageText;
	CryStringT morePlayersText;
};

struct CCoopCinematicPersistent
{
	SCoopCinematicParams m_params;
};

struct CCoopClimbClassExtension
{
};

struct SCoopAssistParams
{
	char pad_0x0000[0x10];
	float singleClimbTime;
	float coopClimbTime;
	float coopClimbAssistingTime;
	float assistEnteringTime0;
	float assistEnteringTime90;
	float assistEnteringTime180;
	float assistStartZoneLength;
	float assistEnteringAnimStartDist;
	Vec3 assistViewOffset;
	Vec3 assistCharacterOffset;
	float climberToAssisterStartDist;
	float assistAnimLength;
	float coopClimbAnimLength;
	float singleClimbAnimLength;
	float singleClimbAnimTime;
	float coopClimbAnimTime;
	float animPlaybackSpeed;
};


struct CCoopAssistClassExtension 
{
	SCoopAssistParams m_params;
};

struct SActionParams
{
	CryStringT action;
	CryStringT tpModel;
	CryStringT agInput;
	CryStringT fpGeometry;
	CryStringT fpAnimName;
	CryStringT fpSoundName;
};

struct CInteractionActionPersistent
{
	char pad_0x0010[0x10];
	std::vector<SActionParams, std::allocator<SActionParams> > m_params;
};

struct SRejectCrossHair
{
	int type;
	int mode;
	int id;
};

struct HoldSActionParams
{
	SRejectCrossHair rejectCrosshair;
	std::vector<CryStringT, std::allocator<CryStringT > > dropActions;
	std::vector<CryStringT, std::allocator<CryStringT > > installActions;
	std::vector<CryStringT, std::allocator<CryStringT > > ignoreActions;
	float speedMult;
	float distNearClipPlane;
	int viewId;
};

struct CHoldEntityPersistent
{
	HoldSActionParams m_params;
};

struct SSpecialMovesPersistents
{
	char pad_0x0008[0x8];
	std::unique_ptr<CClimbClassExtension, std::default_delete<CClimbClassExtension> > climbPersistent;
	std::unique_ptr<CSlidePersistent, std::default_delete<CSlidePersistent> > slidePersistent;
	std::unique_ptr<CKnockBackPersistent, std::default_delete<CKnockBackPersistent> > knockBackPersistent;
	std::unique_ptr<CRaiseAssistPersistent, std::default_delete<CRaiseAssistPersistent> > raiseAssistPersistent;
	std::unique_ptr<CVaultClassExtension, std::default_delete<CVaultClassExtension> > vaultPersistent;
	std::unique_ptr<CCoopCinematicPersistent, std::default_delete<CCoopCinematicPersistent> > coopCinematicPersistent;
	std::unique_ptr<CCoopClimbClassExtension, std::default_delete<CCoopClimbClassExtension> > coopClimbClassExt;
	std::unique_ptr<CCoopAssistClassExtension, std::default_delete<CCoopAssistClassExtension> > coopAssistClassExt;
	std::unique_ptr<CInteractionActionPersistent, std::default_delete<CInteractionActionPersistent> > interactionActionPersistent;
	std::unique_ptr<CHoldEntityPersistent, std::default_delete<CHoldEntityPersistent> > holdEntityPersistent;

};

class CSpecialMovesRegistry
{
public:
	char pad_0x0008[0x8];
	SSpecialMovesPersistents* m_persistents;
};

class CProjectile;

struct SAmmoTypeDesc
{
	SAmmoParam* params;
	std::map<CryStringT, CWeaponSettings*, std::less<CryStringT>, std::allocator<std::pair<CryStringT const, CWeaponSettings*> > > configurations;
};

template <typename T, typename X>
struct VectorMap
{
	std::vector<std::pair<T, X>, std::allocator<std::pair<T, X>>> m_entries;
};

struct CWeaponSystem
{
	char pad_0x00B8[0xB8];
	VectorMap<CEntityClass*, SAmmoTypeDesc> m_ammoparams;
	std::map<unsigned int, CProjectile*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, CProjectile*> > > m_projectiles;
};

struct LaunchParams
{
	unsigned int bulletID;
	Vec3 startPos;
	Vec3 endPos;
	char pierceability;
	bool isTest;
	bool swapped;
	unsigned int shooter;
	int hitID;
};

struct LaunchCallbackData
{
	LaunchParams params;
	void(__cdecl* testCallback)(bool, LaunchParams*);
};

struct SElement
{
	int id;
	DWORD64 time;
	LaunchCallbackData data;
};

struct CLifeTimeQueue
{
	float m_lifeTimeInSeconds;
	int m_idGen;
	std::list<SElement, std::allocator<SElement>> m_elements;
};

class CRWILauncher
{
public:
	CLifeTimeQueue m_rwiRequestsQueue;
};

struct SPlayerSessionResult
{
	CryStringT clan_name;
	int team_id;
	int rank;
	ECharacterClassId character_class;
	int dogTags;
	//int maxKillsInARow;
	int kills;
	int deaths;
	int headshot_kills;
	int melee_kills;
	int explosive_kills;
	int damage_inflicted;
	int damage_received;
	int shooting_accuracy;
	int restore_points;
	int times_resurrected;
	int resurrects_made;
	int killAssistScore;
	SPlayerBanner banner;
	bool info_updated;
	bool stats_updated;
};

struct SPlayerRewardResult
{
	bool IGR;
	bool VIP;
	int money_rewarded;
	int xp_rewarded;
	int sp_rewarded;
	int gainedMoneyBoost;
	int gainedExpBoost;
	int gainedSponsorPointsBoost;
	float percentMoneyBoost;
	float percentExpBoost;
	float percentSponsorPointsBoost;
	int bonusMoney;
	int gainedCrownMoney;
	int bonusXP;
	int bonusSP;
	int score;
	bool noCrownRewards;
	bool firstWinBonus;
	CryStringT dynamicMultipliersInfo;
	float dynamicCrownMultiplier;
};

struct SGameModeData
{
	int total;
	int current;
	int progress;
	int teamScore;
};

enum EVictoryCondition
{
	eVCon_First = 0x0,
	eVCon_None = 0x0,
	eVCon_TDM = 0x1,
	eVCon_CTF = 0x2,
	eVCon_PVE = 0x3,
	eVCon_PTB = 0x4,
	eVCon_STM = 0x5,
	eVCon_FFA = 0x6,
	eVCon_DST = 0x7,
	eVCon_DMN = 0x8,
	eVCon_HNT = 0x9,
	eVCon_TBS = 0xA,
	eVCon_LMS = 0xB,
	eVCon_Count = 0xC,
	eVCon_Default = 0x3,
};

enum EMissionResult
{
	eMRS_Win = 0x0,
	eMRS_Draw = 0x1,
	eMRS_Lose = 0x2,
	eMRS_Count = 0x3,
	eMRS_Default = 0x1,
};

struct CSessionResult
{
	char pad_0x0000[0x30];
	std::map<CryStringT, SPlayerSessionResult, std::less<CryStringT >, std::allocator<std::pair<CryStringT const, SPlayerSessionResult> > > m_playersSession;
	std::map<CryStringT, SPlayerRewardResult, std::less<CryStringT >, std::allocator<std::pair<CryStringT const, SPlayerRewardResult> > > m_playersRewards;
	std::map<unsigned int, unsigned int, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, unsigned int> > > m_performanceMap;
	std::vector<SGameModeData, std::allocator<SGameModeData> > m_GameModeData;
	EVictoryCondition m_GameMode;
	EMissionResult m_SessionResult;
	int m_WinnersTeam;
	int m_ClientTeam;
	bool m_RewardsUpdated;
	CryStringT m_MissionKey;
	CryStringT m_Screenshot;
	int m_screenshotTextureId;
	int m_CompletedStages;
	bool m_DataUpdated;
};

struct SGeneralStats
{
	DWORD64 total_playtime;
	DWORD64 longest_session;
	unsigned __int64 money_accumulated;
	CryStringT favorite_weapon;
};

struct SCommonModeStats
{
	int matches_won;
	int matches_lost;
	int matches_left;
	int kills;
	int kills_friendly;
	int melee_kills;
	int headshots;
	int deaths;
	int kill_streak;
	ECharacterClassId favourite_class;
};

struct SPVPStats : SCommonModeStats
{
	int matches_draw;
};

struct SPVEStats : SCommonModeStats
{
	std::map<CryStringT, int, std::less<CryStringT >, std::allocator<std::pair<CryStringT const, int> > > missions_won_by_type;
	std::map<CryStringT, int, std::less<CryStringT >, std::allocator<std::pair<CryStringT const, int> > > missions_lost_by_type;
	int coins_used;
};

struct SCoopStats
{
	int coop_climbs;
	int coop_assists;
	int resurrects_made;
	__int64 health_restored;
	__int64 armor_restored;
	__int64 ammo_restored;
	int claymore_kills;
};

struct SClassStats
{
	DWORD64 playtime_total;
	DWORD64 playtime_pvp;
	DWORD64 playtime_pve;
	CryStringT favorite_weapon;
	DWORD64 favorite_weapon_use_time;
	__int64 shots;
	__int64 hits;
};

struct SStats
{
	::SGeneralStats general_stats;
	::SPVPStats pvp_stats;
	::SPVEStats pve_stats;
	::SCoopStats coop_stats;
	::SClassStats class_stats[5];
};

class CPersonalStats
{
public:
	// get_player_stats
	char pad_0x018[0x18];
	SStats* m_pCachedStats;
};

template <typename T>
struct Ang3_tpl
{
	T x;
	T y;
	T z;
};

enum ELobbyChatChannel
{
	eCC_First = 0x0,
	eCC_Global = 0x0,
	eCC_Room = 0x1,
	eCC_Team = 0x2,
	eCC_Clan = 0x3,
	eCC_Observer = 0x4,
	eCC_Whisper = 0x5,
	eCC_Count = 0x6,
};

class CLobbyChat
{
private:
	using fnAddServiceMessage = void(__fastcall*)(CLobbyChat*, const char*, ELobbyChatChannel);
public:
	class CMUCChannel
	{
	public:
		void AddServiceMessage(const char* msg) { VirtualFunction<void(__fastcall*)(CLobbyChat::CMUCChannel*, const char*)>(this, 0x18 / 8)(this, msg); }
		bool SendMsg(const char* msg) { return VirtualFunction<bool(__fastcall*)(CLobbyChat::CMUCChannel*, const char*)>(this, 0x20 / 8)(this, msg); }
	};
	char pad_0x0028[0x28];
	CLobbyChat::CMUCChannel* m_channels[6];
	void AddServiceMessage(const char* msg, ELobbyChatChannel channel) { fnAddServiceMessage(0x141385B30)(this, msg, channel); }
};

class CGame
{
public:
	SCVars* GetCVars() { return *(SCVars**)((uint64_t)this + 0x130); }
	COnlineAccount* GetOnlineAccount() { return *(COnlineAccount**)((uint64_t)this + 0x240); } // @ui_cryonline_auth_failed
	CSpecialMovesRegistry* GetSpecialMovesRegistry() { return *(CSpecialMovesRegistry**)((uint64_t)this + 0x280); } // Game/Libs/Config/SpecialMoves.xml
	CFlowchartManager* GetFlowchartManager() { return *(CFlowchartManager**)((uint64_t)this + 0x210); } //  [OnlineAccount] XMPP connection 
	CGameRoom* GetGameRoom() { return *(CGameRoom**)((uint64_t)this + 0x268); } // gameroom_allowaction
	CSessionResult* GetSessionResult() { return *(CSessionResult**)((uint64_t)this + 0x330); }
	CGameFramework* GetGameFramework() { return VirtualFunction<CGameFramework* (__thiscall*)(void*)>(this, 120 / 8)(this); } // 15 original
	CPersonalStats* GetPersonalStats() { return *(CPersonalStats**)((uint64_t)this + 0x2A0); } // get_player_stats
	CLobbyChat* GetLobbyChat() { return *(CLobbyChat**)((uint64_t)this + 0x218); } // @ui_restriction_change_header
	//IOnlineServiceListener* GetOnlineServiceListener() { return *(IOnlineServiceListener**)((uint64_t)this + 0x20); }
	//CAttackPosValidator* GetAttackPosValidator() { return *(CAttackPosValidator**)((uint64_t)this + 0x370); }
	//CWeaponSystem* GetWeaponSystem() { return VirtualFunction<CWeaponSystem* (__thiscall*)(void*)>(this, 320 / 8)(this); }

	// CloseOnline -> sub_1411BAC20
};