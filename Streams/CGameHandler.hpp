// author - saurux | 2023
#pragma once

#include <Header/Header.hpp>

class CGameHandler {
public:
	static void Update() {
		SSystemGlobalEnvironment* pEnv = SSystemGlobalEnvironment::Singleton();
		CGame* pGame = pEnv->GetGame();
		CGameFramework* pGameFramework = pGame->GetGameFramework();
		SCVars* pCVars = pGame->GetCVars();

		if (pCVars) {
			if (Settings::bDisableKickByAFK) {
				pCVars->Set<float>(0x000, 999888777.f);
				pCVars->Set<float>(0x000, 999888777.f);
				pCVars->Set<bool>(0x000, true);
			}

			if (Settings::bVotingEnable) {
				pCVars->Set<float>(0x00, 999.f);
			}
		}

		CActor* mActor = pGameFramework->GetClientActor();

		if (mActor) {
			if (Settings::bSuicide) {
				// Melee Hit
			}
		}
	}
};