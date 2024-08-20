#pragma once

#pragma comment(lib, "Zydis.lib")
#pragma comment(lib, "HookLib.lib")

#include <Hook/HookLib/HookLib.h>

#include "IRMIMessageBody.h"

using pDie = void(__fastcall*)(CNetChannel*);
pDie oDie;

void __stdcall hkDie(CNetChannel* pNetChannel) {
	return;
}

class CNetChannel
{
private:
	char pad_0x0000[0x1D140];
	CryStringT m_nickname;
public:
	using fnDisconnectGame = void(__fastcall*)(CNetChannel*, EDisconnectionCause, CryStringT*);
	void DisconnectGame(EDisconnectionCause cause, CryStringT* msg) { fnDisconnectGame(0x14097ED94)(this, cause, msg); }
	void Disconnect(int cause, const char* fmt = "User left the game") { VirtualFunction<void* (__thiscall*)(void*, int, const char*)>(this, 80 / 8)(this, cause, fmt); }
	void Die() { pDie(0x1409863E4)(this); }

	bool IsConnectionEstablished() { return VirtualFunction<bool(__fastcall*)(void*)>(this, 0xC0 / 8)(this); } // Key establishment handshake ordering error trying to send pending connect
	bool IsLocal() { return VirtualFunction<bool(__fastcall*)(PVOID)>(this, 0xB8 / 8)(this); }
	void DispatchRMI(IRMIMessageBody* pBody) { VirtualFunction<void(__fastcall*)(PVOID, IRMIMessageBody*)>(this, 0xA8 / 8)(this, pBody); }

	CryStringT GetNickname() { return *(CryStringT*)((uint64_t)this + 0x1D140); }
	void SetNickname(const char* name) { this->m_nickname.m_str = name; }

	void InstallHook() {
		oDie = CreateHook<pDie>(reinterpret_cast<void*>(0x1412160D0), hkDie);
	}

	char pad_0x1D168[0x1D168];
	int profile_id;
};