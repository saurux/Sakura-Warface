#pragma once

enum EGameRoomPlayerStatus
{
	eGRPS_NotReady = 0x0,
	eGRPS_Ready = 0x1,
	eGRPS_CantBeReady = 0x2,
};

enum EGameRoomType {

	eGRT_None = 0,
	eGRT_PvE_Private = 1,
	eGRT_PvP_Public = 2,
	eGRT_PvP_ClanWar = 4,
	eGRT_PvP_Autostart = 8,
	eGRT_PvE_Autostart = 0x10,
	eGRT_PvE = 0x11,
	eGRT_PvP_Rating = 0x20,
	eGRT_PvP = 0x2E,
	eGRT_All = 0x3F
};

struct RestrictionValue {

	union unnamed_type_m_values {

		bool boolean;
		int int32;
		__int64 int64;
	};

	BYTE m_valueType[1];
	RestrictionValue::unnamed_type_m_values m_values;
};

struct SRoomCustomParameters {

	RestrictionValue friendlyFire;
	RestrictionValue enemyOutlines;
	RestrictionValue autobalance;
	RestrictionValue joinInTheProcess;
	RestrictionValue classes[5];
	RestrictionValue lockedSpectatorCamera;
	RestrictionValue highLatencyAutoKick;
	RestrictionValue overtimeMode;
	RestrictionValue inventorySlots;
	RestrictionValue maxPlayers;
	RestrictionValue roundLimit;
	RestrictionValue preRoundTime;
};

struct SPlayerStatus
{
	int value;
	const char* placeToken;
	const char* placeInfoToken;
	const char* modeInfoToken;
	const char* missionInfoToken;
};

struct SLobbyUserInfo
{
	unsigned __int64 profileId;
	CryStringT sOnlineId;
	CryStringT sNickname;
	CryStringT sClanName;
	unsigned int experience;
	SPlayerBanner banner;
};

struct SGameRoomPlayerSkill : std::map<CryStringT, float, std::less<CryStringT >, std::allocator<std::pair<CryStringT const, float> > >
{
};

struct SGameRoomPlayerInfo
{
	char teamId;
	CryStringT groupId;
	CryStringT regionId;
	EGameRoomPlayerStatus eStatus;
	bool isOwner;
	bool observer;
	bool isReserved;
	SPlayerStatus presence;
	ECharacterClassId eClassId;
	SLobbyUserInfo user;
	SGameRoomPlayerSkill skill;
};

enum EMissionDifficulty
{
	eMSD_Easy = 0x0,
	eMSD_Normal = 0x1,
	eMSD_Hard = 0x2,
	eMSD_Survival = 0x3,
	eMSD_Tutorial = 0x4,
	eMSD_Count = 0x5,
	eMSD_Default = 0x1,
};

struct SGameRoomMissionObjective
{
	int id;
	CryStringT sType;
};

struct SCrownRewardThresholds
{
	unsigned int values[2][3];
	bool empty;
};

struct SCrownRewards
{
	unsigned int values[3];
};

struct SGameRoomMission
{
	CryStringT sMissionName;
	CryStringT sSetting;
	EMissionDifficulty eDifficulty;
	CryStringT sType;
	CryStringT sDescription;
	CryStringT sMode;
	CryStringT sImage;
	CryStringT sModeName;
	CryStringT sMissionKey;
	bool bNoTeams;
	int objFactor;
	CryStringT sTimeOfDay;
	std::vector<SGameRoomMissionObjective, std::allocator<SGameRoomMissionObjective> > objectives;
	SCrownRewardThresholds crownRewardThresholds;
	SCrownRewards crownRewards;
};

enum ESessionStatus
{
	eGRSS_None = 0x0,
	eGRSS_Starting = 0x1,
	eGRSS_Running = 0x2,
	eGRSS_Finishing = 0x3,
	eGRSS_Failed = 0x4,
};

struct SGameRoomSession
{
	CryStringT id;
	ESessionStatus status;
	float game_progress;
	unsigned __int64 start_time;
};

class SGameRoomInfo
{
public:
	char pad_0x0028[0x28];
	SGameRoomSession session;
	SGameRoomMission mission;
	char pad_0x0260[0x260];
	std::vector<SGameRoomPlayerInfo, std::allocator<SGameRoomPlayerInfo>> m_players;

	using fnGetPlayerInfo = SGameRoomPlayerInfo*(__stdcall*)(SGameRoomInfo*, const char*);
	using fnIsRoomFull = bool * (__stdcall*)(SGameRoomInfo*);
	bool IsRoomFull() { return fnIsRoomFull(0x1414B6110)(this); }
	SGameRoomPlayerInfo* GetPlayerInfo(const char* nickname) { return fnGetPlayerInfo(0x1414B6110)(this, nickname); }
	std::vector<SGameRoomPlayerInfo> GetPlayers() { return m_players; }
};

class CGameRoom
{
private:
	enum EGameRoomState
	{
		eGRS_Left = 0x0,
		eGRS_Joined = 0x1,
		eGRS_Joining = 0x2,
		eGRS_Leaving = 0x3,
	};

	//char pad_0x044C[0x44C];
	//EGameRoomState GetRoomState() { return *(SGameRoomInfo*)((uint64_t)this + 0xF0); }
	bool CheckState() { return !(((*(DWORD*)(this + 0x454) - 1) & 0xFFFFFFFD) != 0); }
public:
	char pad_0x00F0[0xF0];
	SGameRoomInfo m_openedRoom;

	using fnOpenRoom = bool(__fastcall*)(CGameRoom*, EGameRoomType, const char*, const SRoomCustomParameters*, bool, const char*);
	using fnUpdatePvPRoom = bool(__fastcall*)(CGameRoom*, const char*, bool, const SRoomCustomParameters*);
	using fnSetRoomMission = bool(__fastcall*)(CGameRoom*, const char*);
	using fnSetPlayerStatus = bool(__fastcall*)(CGameRoom*, EGameRoomPlayerStatus);
	using fnGetOpenedRoom = SGameRoomInfo*(__fastcall*)(CGameRoom*);
	using fnKick = int(__stdcall*)(CGameRoom*, DWORD64);

	bool OpenRoom(EGameRoomType eRoomType, const char* roomName, const SRoomCustomParameters* params, bool isPrivate, const char* mission_key) { return fnOpenRoom(0x1411D7940)(this, eRoomType, roomName, params, isPrivate, mission_key); }
	bool UpdatePVPRoom(const char* missionKey, bool isPrivate, const SRoomCustomParameters* params) { return fnUpdatePvPRoom(0x1411D3B90)(this, missionKey, isPrivate, params); } // Find -> room_settings_close + 102
	bool SetRoomMission(const char* missionKey) { return fnSetRoomMission(0x1411D6BB0)(this, missionKey); } // Find -> gameroom_setinfo 0xB7 LAST XREF
	bool SetPlayerStatus(EGameRoomPlayerStatus status) { return fnSetPlayerStatus(0x1411E8870)(this, status); } // Find -> game_session_reward - > @msg_autostart_room_join_failed
	// E8 ? ? ? ? 48 81 C4 ? ? ? ? 5D C3
	//SGameRoomInfo* GetOpenedRoomInfo() { return fnGetOpenedRoom(0x1411E7030)(this); } // game_room_can_start
	//int Kick(DWORD64 dwProfileId) { return fnKick(0x1411D3D60)(this, dwProfileId); }
	SGameRoomInfo GetOpenedRoom() { return *(SGameRoomInfo*)((uint64_t)this + 0xF0); }
	EGameRoomState GetRoomState() { return *(EGameRoomState*)((uint64_t)this + 0x454); }
	SGameRoomInfo* GetRoomInfo() { if (GetRoomState() == EGameRoomState::eGRS_Joined) { return &this->m_openedRoom; } else return 0; }
	//SGameRoomInfo GetOpenedRoomInfo() { if (this->m_state != EGameRoomState::eGRS_Left) { return this->m_openedRoom; } }
};