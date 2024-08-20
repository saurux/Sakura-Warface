#pragma once

enum EOnlineError
{
	eOnlineError_NoError = 0x0,
	eOnlineError_StreamError = 0x1,
	eOnlineError_StreamVersionError = 0x2,
	eOnlineError_StreamClosed = 0x3,
	eOnlineError_ProxyAuthRequired = 0x4,
	eOnlineError_ProxyAuthFailed = 0x5,
	eOnlineError_ProxyNoSupportedAuth = 0x6,
	eOnlineError_IoError = 0x7,
	eOnlineError_ParseError = 0x8,
	eOnlineError_ConnectionRefused = 0x9,
	eOnlineError_DnsError = 0xA,
	eOnlineError_OutOfMemory = 0xB,
	eOnlineError_NoSupportedAuth = 0xC,
	eOnlineError_TlsFailed = 0xD,
	eOnlineError_TlsNotAvailable = 0xE,
	eOnlineError_CompressionFailed = 0xF,
	eOnlineError_AuthenticationFailed = 0x10,
	eOnlineError_UserDisconnected = 0x11,
	eOnlineError_NotConnected = 0x12,
	eOnlineError_UnknownError = 0x13,
	eOnlineError_ServiceNotFound = 0x194,
	eOnlineError_ServiceUnavailable = 0x1F7,
	eOnlineError_QoSLimitReached = 0x3EE,
	eOnlineError_MaxOnlineUsersReached = 0x3EF,
	eOnlineError_InvalidSession = 0x3F0,
	eOnlineError_LastingServerFailure = 0x3F1,
	eOnlineError_LostConnection = 0x3F2,
	eOnlineError_QueryTimeout = 0x3F3,
	eOnlineError_TryAgain = 0x3F4,
	eOnlineError_ServerNotFound = 0x3F5,
	eOnlineError_UnknownServer = 0x3F6,
};

#include "COnlineProfile.h"

class COnlineAccount;

enum EOnlineConnectionState
{
	eOnlineConnectionState_Disconnected = 0x0,
	eOnlineConnectionState_Connecting = 0x1,
	eOnlineConnectionState_Connected = 0x2,
	eOnlineConnectionState_Unknown = 0x3,
};

class IOnlineConnection
{
public:
	EOnlineConnectionState GetConnectionState() { return VirtualFunction<EOnlineConnectionState(__thiscall*)(void*)>(this, 64 / 8)(this); }
};

enum EConnectionState
{
	ECS_Disconnected = 0x0,
	ECS_WaitingForCredentials = 0x1,
	ECS_WaitingForConnection = 0x2,
	ECS_WaitingForDisconnect = 0x3,
	ECS_Connected = 0x4,
};

struct IOnlineConnectionListener
{
	void OnConnectionLost(IOnlineConnection* connection, EOnlineError reason, const char* errorDesc) {
		VirtualFunction<void(__fastcall*)(IOnlineConnectionListener*, IOnlineConnection*, EOnlineError, const char*)>(this, 0x10 / 8)(this, connection, reason, errorDesc);
	}
};

using fnFireConnectionLost = void(__stdcall*)(COnlineAccount*, __int32);
fnFireConnectionLost oFireConnectionLost;

void __stdcall hkFireConnectionLost(COnlineAccount* pOnlineAccount, __int32 error)
{
	return;
}

class IOnlineServiceStatusListener {
public:
	virtual void OnPostLogin(const char* cmd) { VirtualFunction<void(__fastcall*)(void*, const char*)>(this, 0x30 / 8)(this, cmd); }
	virtual void OnPostLogout() { VirtualFunction<void(__fastcall*)(void*)>(this, 0x38 / 8)(this); }
};

class IAuthorizationStrategy {
public:
	
};

class COnlineAccount : IOnlineConnectionListener
{
private:
	char pad_0x00E0[0xE0];
	COnlineProfile* m_onlineProfile;

public:
	char pad_0x00B0[0xB0];
	CryStringT m_regionId;
	char pad_0x00C0[0xC0];
	EConnectionState m_state;

	//sub_1412A0F50

	//sub_14116E560
	using fnLogout = void(__stdcall*)(COnlineAccount*, bool);
	using fnConnect = void(__stdcall*)(COnlineAccount*, bool);
	using fnLogin = void(__stdcall*)(COnlineAccount*, const char*, const char*);
	void Connect(bool scheludeDelayed) { return fnConnect(0x14129EBA0)(this, scheludeDelayed); } // @ui_cryonline_auth_failed
	void Login(const char* onlineId, const char* password) { return fnLogin(0x1412CB9A0)(this, onlineId, password); } // @ui_cryonline_auth_failed
	void Logout(bool scheludeDelayed) { return fnLogout(0x1412A0470)(this, scheludeDelayed); } // [OnlineAccount] XMPP connection established
	COnlineAccount* GetThis() { return this; }
	COnlineProfile* GetOnlineProfile() { return *(COnlineProfile**)((uint64_t)this + 0xE0); }
	IOnlineConnectionListener* GetOnlineConnectionListener() { return *(IOnlineConnectionListener**)((uint64_t)this + 0xA); }
	IOnlineConnection* GetConnection() { return *(IOnlineConnection**)((uint64_t)this + 0xD0); }
	EConnectionState GetConnectionState() { return *(EConnectionState*)((uint64_t)this + 0xC0); }

	char pad_0x00F8[0xF8];
	std::vector<IOnlineServiceStatusListener*, std::allocator<IOnlineServiceStatusListener*>> m_statusListeners;

	void OnConnectionLost(IOnlineConnection* pConnection, EOnlineError pError, const char* pErrorDesc){ VirtualFunction<void(__fastcall*)(void*, IOnlineConnection*, EOnlineError, const char*)>(this, 0x10 / 8)(this, pConnection, pError, pErrorDesc); }

	template <class T>
	inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }
	template <class T>
	inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }

	//   void (__fastcall *OnConnectionLost)(IOnlineConnectionListener *this, IOnlineConnection *, EOnlineError, const char *); // 0x10
};