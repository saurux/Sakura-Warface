#pragma once

#define SvRequestShootHit 0x14148AE40 // cmd_kill
#define OffRequestShootHit 0x14255D8E8

#include "CGame.h"
#include "CPhysicalWorld.h"
#include "CEntitySystem.h"
#include "CRenderer.h"
#include "CSystem.h"

#include <chrono>
namespace Chrono
{
	using Clock = std::chrono::steady_clock;
	std::chrono::time_point<std::chrono::steady_clock> start = Clock::now(), now;
	std::chrono::milliseconds duration;

	bool join(int ms)
	{
		while (true)
		{
			now = Clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

			if (duration.count() >= ms)
			{
				start = Clock::now();
				return true;
			}

			return false;
		}
	}
}


class ITimer
{
	enum ETimer
	{
		ETIMER_GAME = 0,
		ETIMER_UI,
		ETIMER_LAST
	};
public:
	float GetFrameTime(ETimer which = ETIMER_GAME) { return VirtualFunction<float(*)(void*, ETimer)>(this, 56 / 8)(this, which); }
};

class SSystemGlobalEnvironment
{
public:
	static SSystemGlobalEnvironment* Singleton() { return *(SSystemGlobalEnvironment**)0x1422C2198; }
	CPhysicalWorld* GetPhysicalWorld() { return *(CPhysicalWorld**)((uint64_t)this + 0x70); }
	CGame* GetGame() { return *(CGame**)((uint64_t)this + 0xD0);}
	CEntitySystem* GetEntitySystem() { return *(CEntitySystem**)((uint64_t)this + 0xE0); }
	CRenderer* GetRenderer() { return *(CRenderer**)((uint64_t)this + 0x48);}
	CSystem* GetSystem() { return *(CSystem**)((uint64_t)this + 0xF0); }
	ITimer* GetTimer() { return *(ITimer**)((uintptr_t)this + 0xC0); }
};

class CMultihitManager
{
public:
	void Update(CActor* mActor)
	{
		Vec3 vShootPosition = SSystemGlobalEnvironment::Singleton()->GetRenderer()->GetViewCamera();
		m_shootHitInfo.shootPos = vShootPosition;
		m_shootHitInfo.profilerId = mActor->Get<BYTE>(0xCE4);
		m_shootHitInfo.shooterId = mActor->GetEntityId();
	}

	void Clear()
	{
		for (auto it = m_shootHitInfo.shoots.begin(); it != m_shootHitInfo.shoots.end(); ++it) it->hits.clear();
		m_shootHitInfo.shoots.clear();
	}

	bool IsEmpty()
	{
		return this->m_shootHitInfo.shoots.empty();
	}

	void AddProjectiles(EntityId projectileId, std::vector<SNetHitInfo> hits)
	{
		this->m_shootHitInfo.shoots.push_back(SShootInfo(projectileId, hits));
	}

	void AddDirection(Vec3 vShootPos, Vec3 vHitPos)
	{
		m_shootHitInfo.dir = vShootPos - vHitPos;
	}

	void SendHits(CActor* pClientActor)
	{
		//if (!this->IsEmpty())
		//{
			//if (PussySettings::pCurrentWeaponIndex == 0)
			//{
				if (CItemProxy* pItemProxy = pClientActor->GetCurrentItem())
				{
					if (CWeapon* pWeapon = pItemProxy->GetWeapon())
					{
						auto cWeaponName = pItemProxy->GetWeaponEntity()->GetName();
						bool bExclusiveWeapon = strstr(cWeaponName, "kn") || strstr(cWeaponName, ("arl")) || strstr(cWeaponName, ("fg")) || strstr(cWeaponName, ("sg")) || strstr(cWeaponName, ("ap")) || strstr(cWeaponName, ("mk")) || strstr(cWeaponName, ("df")) || strstr(cWeaponName, ("cm")) || strstr(cWeaponName, ("ak")) || strstr(cWeaponName, ("ft"));

						if (!bExclusiveWeapon)
						{
							if (Chrono::join(Settings::hitWait))
							{
								CallFunction<void(__fastcall*)(CGameObject*, void*, SRequestShootHit*, int32, int32)>(SvRequestShootHit)(pItemProxy->GetGameObject(), *(void**)OffRequestShootHit, &m_shootHitInfo, 256, -1);
							}
						}
					}
				}
			//}
			/*
			else if (PussySettings::pCurrentWeaponIndex == 1)
			{
				if (CActorInventory* pActorInventory = pClientActor->GetActorInventory())
				{
					if (CWeaponGeneral* pMainWeapon = pActorInventory->GetMainWeapon())
					{
						if (Chrono::join(PussySettings::hitWait))
						{
							CallFunction<void(__fastcall*)(CGameObject*, void*, SRequestShootHit*, int32, int32)>(SvRequestShootHit)(pMainWeapon->GetItemProxy()->GetGameObject(), *(void**)OffRequestShootHit, &m_shootHitInfo, 256, -1);
						}
					}
				}
			}
			else if (PussySettings::pCurrentWeaponIndex == 2)
			{
				if (CActorInventory* pActorInventory = pClientActor->GetActorInventory())
				{
					if (CWeaponGeneral* pPistolWeapon = pActorInventory->GetPistolWeapon())
					{
						if (Chrono::join(Settings::hitWait))
						{
							CallFunction<void(__fastcall*)(CGameObject*, void*, SRequestShootHit*, int32, int32)>(SvRequestShootHit)(pPistolWeapon->GetItemProxy()->GetGameObject(), *(void**)OffRequestShootHit, &m_shootHitInfo, 256, -1);
						}
					}
				}
			}
			*/
		}
	//}
	

private:
	SRequestShootHit m_shootHitInfo;
};