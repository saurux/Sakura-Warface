#include <Header/Header.hpp>

#include <Streams/CAimHandler.hpp>
#include <Streams/CGameHandler.hpp>
#include <Streams/CSM_Handlers.hpp>
#include <Streams/CVisualHandler.hpp>
#include <Streams/CWeaponHandler.hpp>

// hooks
VMTHookManager* iPresent = new VMTHookManager();
VMTHookManager* iResizeBuffers = new VMTHookManager();
// mainly stream

void SGameFrameworkListener::OnPreRender() {
	SSystemGlobalEnvironment* pEnv = SSystemGlobalEnvironment::Singleton();
	CGame* pGame = pEnv->GetGame();
	CGameFramework* pGameFramework = pGame->GetGameFramework();

	if (CRenderer* pRender = pEnv->GetRenderer()) {
		if (iPresent->Initialize((PDWORD64*)pRender->GetSwapChain())) {
			oPresent = (Present)iPresent->dwHookMethod((DWORD64)hkPresent, 8);
		}
		if (iResizeBuffers->Initialize((PDWORD64*)pRender->GetSwapChain())) {
			oResizeBuffers = (pResizeBuffers)iResizeBuffers->dwHookMethod((DWORD64)hkResizeBuffers, 13);
		}
	}

	//CGameHandler::Update();
	//CVisualHandler::Update();
	//CWeaponHandler::Update();
}

class CGeneralStream {
public:
	static void Begin() {
		SSystemGlobalEnvironment* pEnv = SSystemGlobalEnvironment::Singleton();
		CGame* pGame = pEnv->GetGame();
		CGameFramework* pGameFramework = pGame->GetGameFramework();

		pGameFramework->RegisterListener(new SGameFrameworkListener, "", FRAMEWORKLISTENERPRIORITY_GAME);
	}
};