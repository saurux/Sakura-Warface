#pragma once

#include "CActorSystem.h"
#include "CActor.h"
#include "CGameRules.h"
#include "CNetChannel.h"

class CGameFramework;

enum EFRAMEWORKLISTENERPRIORITY {
	FRAMEWORKLISTENERPRIORITY_DEFAULT,
	FRAMEWORKLISTENERPRIORITY_GAME,
	FRAMEWORKLISTENERPRIORITY_HUD,
	FRAMEWORKLISTENERPRIORITY_MENU
};

enum EActionEvent
{
	eAE_channelCreated,
	eAE_channelDestroyed,
	eAE_connectFailed,
	eAE_connected,
	eAE_disconnected,
	eAE_clientDisconnected,
	eAE_disconnectCommandFinished,
	// Map resetting.
	eAE_resetBegin,
	eAE_resetEnd,
	eAE_resetProgress,
	eAE_resetLoadedLevel,    //!< m_value -> 1 if loading new level, 0 otherwise
	eAE_preSaveGame,         //!< m_value -> ESaveGameReason.
	eAE_postSaveGame,        //!< m_value -> ESaveGameReason, m_description: 0 (failed), != 0 (successful).
	eAE_inGame,

	eAE_serverName,          //!< Started server.
	eAE_serverIp,            //!< Obtained server ip.
	eAE_earlyPreUpdate,      //!< Called from CryAction's PreUpdate loop after System has been updated, but before subsystems.
	eAE_demoRecorderCreated,
	eAE_mapCmdIssued,
	eAE_unloadLevel,
	eAE_postUnloadLevel,
	eAE_loadLevel,
};

struct SActionEvent
{
	SActionEvent(EActionEvent e, int val = 0, const char* des = 0) :
		m_event(e),
		m_value(val),
		m_description(des)
	{}
	EActionEvent m_event;
	int          m_value;
	const char* m_description;
};

struct SGameFrameworkListener
{
	virtual ~SGameFrameworkListener() {};
	virtual void OnPostUpdate(float fDeltaTime) {};
	virtual void OnSaveGame(struct ISaveGame* pSaveGame) {};
	virtual void OnLoadGame(struct ILoadGame* pLoadGame) {};
	virtual void OnLevelEnd(const char* nextLevel) {};
	virtual void OnActionEvent(const SActionEvent& event) {};
	virtual void OnPreRender();

	virtual void OnSavegameFileLoadedInMemory(const char* pLevelName) {};
	virtual void OnForceLoadingWithFlash() {};
};

struct SVehicle
{
	CryStringT m_name;
	DWORD64 m_used;
};

struct SVehicles
{
	bool m_inVehicle;
	DWORD64 m_enteredVehicle;
	std::vector<SVehicle, std::allocator<SVehicle> > m_vehicles;
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<SVehicle> > > m_curVehicle;
};

struct SWeapon
{
	CryStringT m_name;
	DWORD64 m_used;
	int m_kills;
	int m_shots;
	int m_hits;
	int m_reloads;
	float m_damage;
};

struct SWeapons
{
	std::vector<SWeapon, std::allocator<SWeapon> > m_weapons;
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<SWeapon> > > m_curWeapon;
	DWORD64 m_selected;
};

struct SSuitMode
{
	DWORD64 m_lastTime;
	int m_currentMode;
	int m_kills[4];
	DWORD64 m_used[4];
};

struct SPlayerPos
{
	Vec3 pos;
	Vec3 fwd;
	float terrainHeight;
	float camHeight;
};

struct SPlayerEvent
{
	CryStringT event;
	CryStringT str_param;
	int int_param;
	Vec3 vec3_param;
	float float_param;
	CryStringT str_2_param;
};

template <typename T>
struct TTimeStampedData
{
	std::vector<std::pair<DWORD64, T>, std::allocator<std::pair<DWORD64, T> > > m_data;
};

struct SPlayerStats
{
	char pad_0x0010[0x10];
	int m_kills;
	int m_deaths;
	int m_shots;
	int m_hits;
	int m_melee;
	int m_revives;
	bool m_inVehicle;
	DWORD64 m_started;
	DWORD64 m_ended;
	SVehicles m_vehicles;
	SWeapons m_weapons;
	SSuitMode m_suit;
	bool m_dead;
	TTimeStampedData<SPlayerPos> m_positions;
	TTimeStampedData<SPlayerEvent> m_events;
};

struct SPlayerInfo
{
	CryStringT name;
	int team;
	int rank;
	bool spectator;
	std::map<CryStringT, int, std::less<CryStringT>, std::allocator<std::pair<CryStringT const, int> > > scores;
	int id;
	std::vector<_smart_ptr<SPlayerStats>, std::allocator<_smart_ptr<SPlayerStats> > > stats;
};

struct STeamStats
{
	int id;
	CryStringT name;
	int score;
};

class CGameStatistics
{
public:
	char pad_0x0138[0x138];
	DWORD64 m_reportCounter;
};

class CStatsTrack
{
public:
	char pad_0x0040[0x40];
	CSmartScriptTable m_scriptTable;
	CGameStatistics* m_pGameStats;
};

struct SRoundStats
{
	CryStringT m_mapName;
	int m_roundTime;
	int m_victoryCondition;
	bool m_respawn;
	int m_ranked;
	int m_round;
	int m_winner;
	DWORD64 m_start;
	DWORD64 m_duration;
};

class CGameStats
{
public:
	//char pad_0x0020[0x20];
	//CGameFramework* m_pGameFramework;
	//CActorSystem* m_pActorSystem;
	//bool m_playing;
	//bool m_stateChanged;
	//bool m_startReportNeeded;
	//bool m_reportStarted;
	char pad_0x0020[0x38];
	std::map<int, SPlayerInfo, std::less<int>, std::allocator<std::pair<int const, SPlayerInfo> > > m_playerMap;
	std::map<int, STeamStats, std::less<int>, std::allocator<std::pair<int const, STeamStats> > > m_teamMap;
	CStatsTrack* m_statsTrack;
	//IServerReport* m_serverReport;
	//CGameStats::Listener* m_pListener;
	//CTimeValue m_lastUpdate;
	//CTimeValue m_lastReport;
	//CryStringT m_gameMode;
	//CryStringT m_mapName;
	//CGameStatsConfig* m_config;
	//CTimeValue m_lastPosUpdate;
	//CTimeValue m_roundStart;
	//std::auto_ptr<SRoundStats> m_roundStats;
};

struct SEntityHits
{
	SEntityHits* pnext;
	Vec3* pHits;
	Vec3 hit0;
	int* pnHits;
	int nhits0;
	int nHits;
	int nHitsAlloc;
	float hitRadius;
	int hitpoints;
	int maxdmg;
	int nMaxHits;
	float timeUsed;
	float lifeTime;
};

class CActionGame
{
public:
	char pad_0x0000[0x228];
	CGameStats* m_pGameStats;
	SEntityHits* m_pEntHits0;
	std::map<int, SEntityHits*, std::less<int>, std::allocator<std::pair<int const, SEntityHits*> > > m_mapEntHits;
};

class CGameFramework
{
public:
	//CActorSystem* GetActorSystem() { return *(CActorSystem**)((uint64_t)this + 0x4E0);}
	CActionGame* GetActionGame() { return *(CActionGame**)((uint64_t)this + 0x50);  }
	CActorSystem* GetActorSystem() { return VirtualFunction<CActorSystem* (__thiscall*)(void*)>(this, 200 / 8)(this); }
	CGameRules* GetGameRules() { return VirtualFunction<CGameRules* (__thiscall*)(void*)>(this, 1096 / 8)(this); }
	CActor* GetClientActor() { CActor* pNewActor = 0; if (VirtualFunction<bool(__thiscall*)(void*, CActor**)>(this, 1136 / 8)(this, &pNewActor)) { return pNewActor; } else { return 0; } }
	CNetChannel* GetClientChannel() { return VirtualFunction<CNetChannel* (__thiscall*)(void*)>(this, 568 / 8)(this); }
	DWORD64 GetServerTime() { DWORD64 dwTime = 0; VirtualFunction<void(__thiscall*)(void*, DWORD64*)>(this, 73)(this, &dwTime); return dwTime; }
	void RegisterListener(SGameFrameworkListener* pGameFrameworkListener, const char* name, EFRAMEWORKLISTENERPRIORITY eFrameworkListenerPriority) { VirtualFunction<void(__thiscall*)(void*, SGameFrameworkListener*, const char*, EFRAMEWORKLISTENERPRIORITY)>(this, 864 / 8)(this, pGameFrameworkListener, name, eFrameworkListenerPriority); }
	void UnregisterListener(SGameFrameworkListener* pGameFrameworkListener) { VirtualFunction<void(__thiscall*)(PVOID, SGameFrameworkListener*)>(this, 872 / 8)(this, pGameFrameworkListener); }
};
