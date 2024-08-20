#pragma once

#include <Header/Header.hpp>

class CWeaponHandler {
public:
	static void Update() {
		SSystemGlobalEnvironment* pEnv = SSystemGlobalEnvironment::Singleton();
		CGame* pGame = pEnv->GetGame();
		CGameFramework* pGameFramework = pGame->GetGameFramework();

		CActor* mActor = pGameFramework->GetClientActor();

		if (mActor) {
			if (CItemProxy* pItemProxy = mActor->GetCurrentItem()) {
				if (CWeaponGeneral* pWeaponGeneral = pItemProxy->GetWeaponGeneral()) {
					if (CWeaponParameters* pWeaponParameters = pWeaponGeneral->GetWeaponParameters()) {
						if (Settings::bNoRecoil) {
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_RclAtt, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_RclDec, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_RclDecDelay, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_RclMax, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_RclSmth, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_RclRnd, 0.f);
						}

						if (Settings::bNoSpread) {
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SprdAtt, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SprdDec, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SprdDecDelay, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SprdInverted, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SprdMax, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SprdMin, 0.f);
						}

						if (Settings::bNoSway) {
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SwayDec, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SwayMinX, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SwayMinY, 0.f);
						}

						if (Settings::bFastZoom) {
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_ZoomInDuration, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_ZoomInDurationBuff, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_ZoomOutDuration, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_ZoomOutDurationBuff, 0.f);
						}

						if (Settings::bFastKnife) {
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_MeleeDuration, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_MeleeDurationBuff, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SecondaryMeleeDuration, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SecondaryMeleeDurationBuff, 0.f);
							pWeaponParameters->GetStatsArray()->SetValue(EGameStatType::eGS_SecondaryMeleeOutDuration, 0.f);
						}
					}
				}
			}
		}
	}
};