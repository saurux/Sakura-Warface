#pragma once

#include <Settings/Sakura.hpp>

#include <SDK/Math/Math.h>

#include <SDK/SSystemGlobalEnvironment.h>
#include <SDK/CGame.h>
#include <SDK/CGameFramework.h>
#include <SDK/CActorSystem.h>
#include <SDK/CActor.h>
#include <SDK/CEntitySystem.h>
#include <SDK/CEntityIterator.h>
#include <SDK/CEntity.h>

void SetVisionParams(CEntity* pEntity, Color_tpl<float>* color, EHUDSilhouetteVisibility type, bool bDisableAtMin = false, float nearDist = 1000.f) {
	CallFunction<void(__fastcall*)(DWORD64, int, Color_tpl<float>*, bool, float)>(Off_SetVisionParams)(0, pEntity->GetEntityId(), color, bDisableAtMin, nearDist);
} // HudSilhouettes_Type -> xref last

Color_tpl<float> pObjectColor;
Color_tpl<float> pEntityColor;
Color_tpl<float> pWeaponColor;
class CVisualHandler {
public:
	static void Update() {
		SSystemGlobalEnvironment* pEnv = SSystemGlobalEnvironment::Singleton();
		CGame* pGame = pEnv->GetGame();
		CGameFramework* pGameFramework = pGame->GetGameFramework();

		CActor* mActor = pGameFramework->GetClientActor();
		CActorSystem* pActorSystem = pGameFramework->GetActorSystem();

		if (mActor) {
			CEntitySystem* pEntitySystem = pEnv->GetEntitySystem();
			CEntityIterator* pEntityIt = pEntitySystem->GetEntityIterator();

			if (Settings::bClaymoreDetectRadius) {
				pGame->GetCVars()->Set<float>(0xF1C, 9999.f); // claymore_detector_radius
			}

			if (Settings::bFlashbangDisable) {
				if (CRenderer* pRenderer = pEnv->GetRenderer()) {
					pRenderer->SetPostEffectParam<float>("Flashbang_Time", 0.f);
				}
			}

			for (; CEntity * pEntity = pEntityIt->Next();) {
				if (Settings::bSilhouetteObject) {
					if (strstr(pEntity->GetName(), "S02_ShootingTarget_duck")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "_Lootbox")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "BOSS2_Stage2_ShootingTarget_Level1_Capsule")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "_BOSS2_Stage2_ShootingTarget_Level2_Capsule")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "ShootingTarget_Stage3_Core")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "ammo")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "BombGeometry")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "BombEntity")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "bomb")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "S00_ShootingTarget_Top")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "S00_ShootingTarget_Bottom")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
					if (strstr(pEntity->GetName(), "S00_ShootingTarget_Claymore4")) {
						SetVisionParams(pEntity, &pObjectColor, Always);
					}
				}

				if (Settings::bSilhouetteWeapon) {
					if (strstr(pEntity->GetEntityClass()->GetName(), "InventoryPickup") || pEntity->GetFlags() == 0x480012 || pEntity->GetFlags() == 0x80000) {
						SetVisionParams(pEntity, &pWeaponColor, Always);
					}
				}

				if (CActor* pActor = pActorSystem->GetActor(pEntity->GetEntityId())) {
					if (pActorSystem->IsNotMyTeam(mActor, pActor)) {
						if (!pActor->IsDead()) {
							if (Settings::bSilhouettePlayer) {
								SetVisionParams(pActor->GetEntity(), &pEntityColor, Always);
							}
						}
					}
				}
			}
		}
	}
};