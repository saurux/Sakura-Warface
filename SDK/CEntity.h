#pragma once

#include "CEntityProxy.h"
#include "CEntityClass.h"
#include "CCharacterInstance.h"
#include "CGameObject.h"
#include "CPhysicalWorld.h"

enum EEntityProxy : __int32
{
	ENTITY_PROXY_RENDER = 0x0,
	ENTITY_PROXY_PHYSICS = 0x1,
	ENTITY_PROXY_SCRIPT = 0x2,
	ENTITY_PROXY_SOUND = 0x3,
	ENTITY_PROXY_AI = 0x4,
	ENTITY_PROXY_AREA = 0x5,
	ENTITY_PROXY_BOIDS = 0x6,
	ENTITY_PROXY_BOID_OBJECT = 0x7,
	ENTITY_PROXY_CAMERA = 0x8,
	ENTITY_PROXY_FLOWGRAPH = 0x9,
	ENTITY_PROXY_TRACKVIEW = 0xA,
	ENTITY_PROXY_SUBSTITUTION = 0xB,
	ENTITY_PROXY_TRIGGER = 0xC,
	ENTITY_PROXY_ROPE = 0xD,
	ENTITY_PROXY_ENTITYNODE = 0xE,
	ENTITY_PROXY_USER = 0xF,
	ENTITY_PROXY_LAST = 0x10,
};

struct SScriptTableFunc
{
	void* ptr;
	int nRef;
};

struct IScriptTable{};
struct SScriptFuncHandle{};

enum ScriptAnyType
{
	ANY_ANY = 0x0,
	ANY_TNIL = 0x1,
	ANY_TBOOLEAN = 0x2,
	ANY_THANDLE = 0x3,
	ANY_TNUMBER = 0x4,
	ANY_TSTRING = 0x5,
	ANY_TTABLE = 0x6,
	ANY_TFUNCTION = 0x7,
	ANY_TUSERDATA = 0x8,
	ANY_TVECTOR = 0x9,
	ANY_COUNT = 0xA,
};

struct ScriptAnyHandle
{
	bool b;
	float number;
	const char* str;
	IScriptTable* table;
	const void* ptr;
	SScriptFuncHandle* function;
	Vec3 vec3;
	SScriptTableFunc ud;
};

struct ScriptAnyValue
{
	ScriptAnyType type;
	ScriptAnyHandle handle;
};

class CSmartScriptTable
{
public:
	void Release() { VirtualFunction<void (__thiscall*)(void*)>(this, 16 / 8)(this); }
	void SetValueAny(const char* sKeyName, ScriptAnyValue& any, bool bChain = 0) { VirtualFunction<void (__thiscall*)(void*, const char*, ScriptAnyValue&, bool)>(this, 48 / 8)(this, sKeyName, any, bChain); }
	bool GetValueAny(const char* sKeyName, ScriptAnyValue& any, bool bChain = 0) { return VirtualFunction<bool (__thiscall*)(void*, const char*, ScriptAnyValue&, bool)>(this, 56 / 8)(this, sKeyName, any, bChain); }

	using fnGetValueFloat = bool(__fastcall*)(CSmartScriptTable*, const char*, float*);
	bool GetValueFloat(const char* sKey, float* fValue) { return fnGetValueFloat(0x140583290)(this, sKey, fValue); }
	// engine_maxrpm
	using fnSetValueFloat = void(__fastcall*)(CSmartScriptTable*, const char*, float*);
	void SetValueFloat(const char* sKey, float* fValue) { fnSetValueFloat(0x140587D30)(this, sKey, fValue); }
	// dynamic_crown_multiplier

	using fnGetValueInt = float(__fastcall*)(CSmartScriptTable*, const char*, int*);
	int GetValueInt(const char* sKey, int* fValue) { return fnGetValueInt(0x140587650)(this, sKey, fValue); }

	using fnGetValueBoolean = bool(__fastcall*)(CSmartScriptTable*, const char*, bool*);
	bool GetValueBoolean(const char* sKey, bool* bValue) { return fnGetValueBoolean(0x1405878A0)(this, sKey, bValue); }
};

class CScriptTable
{
public:
	CSmartScriptTable* GetSmartScriptTable() { return VirtualFunction<CSmartScriptTable* (__thiscall*)(void*)>(this, 112 / 8)(this); }
};

/*
enum EEntityXFormFlags
{
	ENTITY_XFORM_POS = 0x2,
	ENTITY_XFORM_ROT = 0x4,
	ENTITY_XFORM_SCL = 0x8,
	ENTITY_XFORM_NO_PROPOGATE = 0x10,
	ENTITY_XFORM_FROM_PARENT = 0x20,
	ENTITY_XFORM_PHYSICS_STEP = 0x2000,
	ENTITY_XFORM_EDITOR = 0x4000,
	ENTITY_XFORM_TRACKVIEW = 0x8000,
	ENTITY_XFORM_TIMEDEMO = 0x10000,
	ENTITY_XFORM_NOT_REREGISTER = 0x20000,
	ENTITY_XFORM_NO_EVENT = 0x40000,
	ENTITY_XFORM_NO_SEND_TO_ENTITY_SYSTEM = 0x80000,
	ENTITY_XFORM_USER = 0x1000000,
};

CSoundProxy_vtbl
{
  void(__fastcall * ~IEntityProxy)(IEntityProxy * this);
  void(__fastcall* GetMemoryUsage)(IEntityProxy* this, ICrySizer*);
  EEntityProxy(__fastcall* GetType)(IEntityProxy* this);
  bool(__fastcall* Init)(IEntityProxy* this, IEntity*, SEntitySpawnParams*);
  void(__fastcall* Reload)(IEntityProxy* this, IEntity*, SEntitySpawnParams*);
  void(__fastcall* Done)(IEntityProxy* this);
  void(__fastcall* Release)(IEntityProxy* this);
  void(__fastcall* Update)(IEntityProxy* this, SEntityUpdateContext*);
  void(__fastcall* ProcessEvent)(IEntityProxy* this, SEntityEvent*);
  void(__fastcall* SerializeXML)(IEntityProxy* this, XmlNodeRef*, bool, IEntitiesLoadContext*);
  void(__fastcall* Serialize)(IEntityProxy* this, CSerializeWrapper<ISerialize>);
  bool(__fastcall* NeedSerialize)(IEntityProxy* this);
  bool(__fastcall* GetSignature)(IEntityProxy* this, CSerializeWrapper<ISerialize>);
  void(__fastcall* SetFlags)(IEntitySoundProxy* this, int);
  int(__fastcall* GetFlags)(IEntitySoundProxy* this);
  ISound* (__fastcall* GetSound)(IEntitySoundProxy* this, unsigned int);
  ISound* (__fastcall* GetSoundByIndex)(IEntitySoundProxy* this, unsigned int);
  unsigned int(__fastcall* PlaySound)(IEntitySoundProxy* this, const char*, const Vec3_tpl<float>*, const Vec3_tpl<float>*, unsigned int, ESoundSemantic);
  unsigned int(__fastcall* PlaySound)(IEntitySoundProxy* this, const char*, const Vec3_tpl<float>*, const Vec3_tpl<float>*, unsigned int, ESoundSemantic, unsigned int*, int);
  bool(__fastcall* PlaySound)(IEntitySoundProxy* this, ISound*, const Vec3_tpl<float>*, const Vec3_tpl<float>*, float, bool);
  unsigned int(__fastcall* PlaySoundEx)(IEntitySoundProxy* this, const char*, const Vec3_tpl<float>*, const Vec3_tpl<float>*, unsigned int, float, float, float, ESoundSemantic, unsigned int*, int);
  unsigned int(__fastcall* PlaySoundEx)(IEntitySoundProxy* this, const char*, const Vec3_tpl<float>*, const Vec3_tpl<float>*, unsigned int, float, float, float, ESoundSemantic);
  bool(__fastcall* SetStaticSound)(IEntitySoundProxy* this, unsigned int, bool);
  bool(__fastcall* GetStaticSound)(IEntitySoundProxy* this, const unsigned int);
  void(__fastcall* StopSound)(IEntitySoundProxy* this, unsigned int, ESoundStopMode);
  void(__fastcall* PauseSound)(IEntitySoundProxy* this, unsigned int, bool);
  void(__fastcall* StopAllSounds)(IEntitySoundProxy* this);
  void(__fastcall* SetSoundPos)(IEntitySoundProxy* this, unsigned int, const Vec3_tpl<float>*);
  Vec3_tpl<float>* (__fastcall* GetSoundPos)(IEntitySoundProxy* this, Vec3_tpl<float>* result, unsigned int);
  void(__fastcall* SetSoundDirection)(IEntitySoundProxy* this, unsigned int, const Vec3_tpl<float>*);
  Vec3_tpl<float>* (__fastcall* GetSoundDirection)(IEntitySoundProxy* this, Vec3_tpl<float>* result, unsigned int);
  void(__fastcall* SetEffectRadius)(IEntitySoundProxy* this, float);
  float(__fastcall* GetEffectRadius)(IEntitySoundProxy* this);
  const char* (__fastcall* GetTailName)(IEntitySoundProxy* this);
  void(__fastcall* CheckVisibilityForTailName)(IEntitySoundProxy* this, const float, const float);
  void(__fastcall* UpdateSounds)(IEntitySoundProxy* this);
  IEntity* (__fastcall* GetEntity)(IEntitySoundProxy* this);
};

*/

enum ESoundSemantic
{
	eSoundSemantic_None = 0x0,
	eSoundSemantic_OnlyVoice = 0x1,
	eSoundSemantic_NoVoice = 0x2,
	eSoundSemantic_Sandbox = 0x4,
	eSoundSemantic_Unused1 = 0x8,
	eSoundSemantic_Unused2 = 0x10,
	eSoundSemantic_Unused3 = 0x20,
	eSoundSemantic_Ambience = 0x40,
	eSoundSemantic_Ambience_OneShot = 0x80,
	eSoundSemantic_Physics_Collision = 0x100,
	eSoundSemantic_Dialog = 0x200,
	eSoundSemantic_MP_Chat = 0x400,
	eSoundSemantic_Physics_Footstep = 0x800,
	eSoundSemantic_Physics_General = 0x1000,
	eSoundSemantic_HUD = 0x2000,
	eSoundSemantic_Replay = 0x4000,
	eSoundSemantic_FlowGraph = 0x8000,
	eSoundSemantic_Player_Foley_Voice = 0x10000,
	eSoundSemantic_Living_Entity = 0x20000,
	eSoundSemantic_Mechanic_Entity = 0x40000,
	eSoundSemantic_NanoSuit = 0x80000,
	eSoundSemantic_SoundSpot = 0x100000,
	eSoundSemantic_Particle = 0x200000,
	eSoundSemantic_AI_Pain_Death = 0x400000,
	eSoundSemantic_AI_Readability = 0x800000,
	eSoundSemantic_AI_Readability_Response = 0x1000000,
	eSoundSemantic_TrackView = 0x2000000,
	eSoundSemantic_Projectile = 0x4000000,
	eSoundSemantic_Vehicle = 0x8000000,
	eSoundSemantic_Weapon = 0x10000000,
	eSoundSemantic_Explosion = 0x20000000,
	eSoundSemantic_Player_Foley = 0x40000000,
	eSoundSemantic_Animation = 0x80000000,
};

class CSoundProxy
{
public:
	// PlaySound - 0x88
	EntityId PlaySound(const char* soundName, const Vec3_tpl<float>* vOffset, const Vec3_tpl<float>* vDirection, unsigned int nSoundFlags, ESoundSemantic eSemantic)
	{
		VirtualFunction<EntityId(__fastcall*)(CSoundProxy*, const char*, const Vec3_tpl<float>*, const Vec3_tpl<float>*, unsigned int, ESoundSemantic)>(this, 0x88 / 8)(this, soundName, vOffset, vDirection, nSoundFlags, eSemantic);
	}
};

class CEntity
{
private:
	char pad_0x0000[0x18]; //0x0000
	EntityId dwEntityId; //0x0018 
public:
	EntityId GetEntityId() { return this->dwEntityId; }
	const char* GetName() { return VirtualFunction<const char* (__thiscall*)(void*)>(this, 96 / 8)(this); }
	void SetName(const char* name) { VirtualFunction<void(__thiscall*)(void*, const char*)>(this, 88 / 8)(this, name); }
	bool IsHidden() { return VirtualFunction<bool(__fastcall*)(void*)>(this, 376 / 8)(this); }
	bool IsInvisible(){ return VirtualFunction<bool(__thiscall*)(void*)>(this, 49)(this); }
	void SetWorldTM(Matrix34* tm, int nWhyFlags = 0) { return VirtualFunction<void (__thiscall*)(void*, Matrix34*, int)>(this, 0xA8 / 8)(this, tm, nWhyFlags); }
	Matrix34& GetWorldTM() { return VirtualFunction<Matrix34& (__thiscall*)(void*)>(this, 0xB8 / 8)(this); }
	void GetWorldBounds(AABB& bbox) { VirtualFunction<void(__thiscall*)(void*, AABB&)>(this, 0xC8 / 8)(this, bbox); }
	Vec3 GetCenterPosition() { AABB aabb; this->GetWorldBounds(aabb); return aabb.GetCenter(); }
	void SetPosition(const Vec3& vPos, int nWhyFlags) { VirtualFunction<void(__thiscall*)(void*, const Vec3&, int)>(this, 0xD8 / 8)(this, vPos, nWhyFlags); }
	Vec3& GetWorldPosition() { return VirtualFunction<Vec3& (__fastcall*)(PVOID)>(this, 224 / 8)(this); }
	void InvalidateTM(int nWhyFlags) { VirtualFunction<void(__thiscall*)(PVOID, int)>(this, 768 / 8)(this, nWhyFlags); }
	void SetLocation(const Vec3& vPos, int nWhyFlags = 0) { GetWorldPosition() = vPos; InvalidateTM(nWhyFlags | 1); }
	void SetLocalPos(Vec3& LocalPos, int64 Flag = 0) { this->Set<Vec3>(0x70, LocalPos); VirtualFunction<void(__fastcall*)(PVOID, Vec3&, int64)>(this, 0xD8 / 8)(this, LocalPos, Flag); this->InvalidateTM(Flag | ENTITY_XFORM_POS | ENTITY_XFORM_NO_SEND_TO_ENTITY_SYSTEM | ENTITY_XFORM_NOT_REREGISTER);
	}
	Vec3 GetForwardDir() { return VirtualFunction<Vec3(__thiscall*)(void*)>(this, 288 / 8)(this); }
	Quat GetEntityRotation() { return VirtualFunction<Quat(__thiscall*)(void*)>(this, 0xF0 / 8)(this); }
	bool IsObjectDead() { float f1 = 1; if (this->GetEntityScripts()->GetSmartScriptTable()->GetValueFloat("currentHealth", &f1)) return f1 <= 0; }
	bool IsShootingTatgetDead() { int f1= 1; if(this->GetEntityScripts()->GetSmartScriptTable()->GetValueInt("currentHealth", &f1)) return f1 <= 0; }
	int GetObjectHealth() { int f1 = 1; if (this->GetEntityScripts()->GetSmartScriptTable()->GetValueInt("currentHealth", &f1)) return f1; }
	bool IsObjectActivated() { bool b1 = 0; if(this->GetEntityScripts()->GetSmartScriptTable()->GetValueBoolean("activated", &b1)) return b1; }
	void SendEvent(const char* animName, void* pActor) { int p = 0x10; VirtualFunction<void(__thiscall*)(void*, int*, const char*, void*)>(this, 344 / 8)(this, &p, animName, pActor); }
	IPhysicalEntity* GetPhysics() { return VirtualFunction<IPhysicalEntity* (__thiscall*)(void*)>(this, 504 / 8)(this); }
	CEntityProxy* GetProxy(EEntityProxy proxy = EEntityProxy::ENTITY_PROXY_RENDER) { return VirtualFunction<CEntityProxy* (__thiscall*)(void*, EEntityProxy)>(this, 472 / 8)(this, proxy); }
	CSoundProxy* GetSound(EEntityProxy proxy = EEntityProxy::ENTITY_PROXY_SOUND) { return VirtualFunction<CSoundProxy* (__thiscall*)(void*, EEntityProxy)>(this, 472 / 8)(this, proxy); }
	CScriptTable* GetEntityScripts(EEntityProxy proxy = EEntityProxy::ENTITY_PROXY_SCRIPT) { return VirtualFunction<CScriptTable* (__thiscall*)(void*, EEntityProxy)>(this, 472 / 8)(this, proxy); }
	CEntityClass* GetEntityClass() { return VirtualFunction<CEntityClass* (__fastcall*)(void*)>(this, 0x18 / 8)(this); }
	CCharacterInstance* GetCharacter(int nSlot) { return VirtualFunction<CCharacterInstance* (__thiscall*)(void*, int)>(this, 664 / 8)(this, nSlot); }
	//void SetMaterial(CMaterial* pMaterial) { VirtualFunction<void(__thiscall*)(void*, CMaterial*)>(this, 544 / 8)(this, pMaterial); }
	int LoadCharacter(int nSlot, const char* filename, int nLoadFlags) { return VirtualFunction<int (__thiscall*)(void*, int, const char*, int)>(this, 720 / 8)(this, nSlot, filename, nLoadFlags); }
	Vec3 GetWorldPos() { Matrix34 m = this->GetWorldTM(); return m.GetTranslation(); }
	int GetFlags() {return VirtualFunction<int(__thiscall*)(void*)>(this, 0x30 / 8)(this);}
	CGameObject* GetGameObject() { return reinterpret_cast<CGameObject*>(this->GetProxy(EEntityProxy::ENTITY_PROXY_ENTITYNODE)); }
	Vec3 GetPosition() { return this->Get<Vec3>(0x70); }
	Quat GetRotation() { return *(Quat*)((DWORD64)this + 0x88); }
	void SetRotation(Quat qRotation) { *(Quat*)((DWORD64)this + 0x88) = qRotation; }
	QuatT_tpl<float> GetRotationQuat() { return *(QuatT_tpl<float>*)((DWORD64)this + 0x88); }

	template <typename T>
	inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }
	template <typename T>
	inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }

	bool IsEntityRight()
	{
		if (strstr(this->GetName(), ("TurretAPC")) && strstr(this->GetName(), ("Black_Wolf")) && strstr(this->GetName(), ("Mech2300"))
			&& strstr(this->GetName(), ("Artillery")) && strstr(this->GetName(), ("_TurretAPC")) && strstr(this->GetName(), ("_Turret_MG_OneShot"))
			&& strstr(this->GetName(), ("Tank_Turret")))
		{
			return false;
		}

		return true;
	}

	char pad_0000[0x70]; //0x0000
	Vec3 m_vPos; //0x0070
	Vec3 m_vScale; //0x007C
	Quat m_qRotation; //0x0088
};