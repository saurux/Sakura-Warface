#pragma region Includes

#include <Hook/vmthook.h>
#include <Render/Hooks.hpp>

#include <d3d11.h>
#include <Render/imgui/imgui.h>
#include <Render/imgui/imgui_impl_dx11.h>
#include <Render/imgui/imgui_impl_win32.h>

#include <Settings/Sakura.hpp>

#include <Offsets/Offsets.hpp>

#include <Functions/Caller.hpp>

#include <SDK/Math/Math.h>

#include <SDK/SSystemGlobalEnvironment.h>
#include <SDK/CGame.h>
#include <SDK/CGameFramework.h>
#include <SDK/CActorSystem.h>
#include <SDK/CActor.h>
#include <SDK/CEntity.h>
#include <SDK/CEntityClass.h>
#include <SDK/CEntityIterator.h>
#include <SDK/CEntitySystem.h>
#include <SDK/CGameObject.h>
#include <SDK/CGameRoom.h>
#include <SDK/CGameRules.h>
#include <SDK/CCharacterInstance.h>
#include <SDK/CSkeletonPose.h>
#include <SDK/CItemProxy.h>
#include <SDK/CWeapon.h>
#include <SDK/CWeaponGeneral.h>
#include <SDK/CWeaponNetwork.h>
#include <SDK/CWeaponSettings.h>
#include <SDK/CWorldQuery.h>
#include <SDK/COnlineAccount.h>
#include <SDK/COnlineProfile.h>
#include <SDK/CMovementController.h>
#include <SDK/CSpecialMovesRegistry.h>
#pragma endregion