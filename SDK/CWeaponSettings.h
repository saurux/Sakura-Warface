#pragma once

class CWeaponSettings
{
public:
	virtual ~CWeaponSettings() = 0;
	virtual int GetAmmoCount() = 0;
	virtual void SetAmmoCount(int count) = 0;
	virtual void ExpendAmmo() = 0;
	virtual bool IsEmpty() = 0;
	virtual bool IsBarrel() = 0;
	virtual bool IsRechargeable() = 0;
	virtual bool RunLevelNotification() = 0;

	void m_pStopAmmoCounter(bool force) { *(bool*)((uintptr_t)this + 0x8) = force; }
};

enum EAmmoKind
{
	eAK_Bullet = 0x0,
	eAK_GrapeShot = 0x1,
	eAK_ExplosiveGrenade = 0x2,
	eAK_PoisonGrenade = 0x3,
	eAK_FlashGrenade = 0x4,
	eAK_SmokeGrenade = 0x5,
	eAK_EMPGrenade = 0x6,
	eAK_ClaymoreExplosive = 0x7,
	eAK_C4Explosive = 0x8,
	eAK_Medkit = 0x9,
	eAK_GLGrenade = 0xA,
	eAK_Count = 0xB,
	eAK_Default = 0x0,
	eAK_Error = 0xB,
};

enum ELaunchType
{
	eLT_None = 0xFFFFFFFF,
	eLT_Phys = 0x0,
	eLT_RWI = 0x1,
};

enum EPhysicalizationType
{
	ePT_None = 0x0,
	ePT_Particle = 0x1,
	ePT_Rigid = 0x2,
	ePT_Static = 0x3,
};

struct pe_params
{
	int type;
};

struct pe_params_particle : pe_params
{
	unsigned int flags;
	float mass;
	float size;
	float thickness;
	Vec3 heading;
	float velocity;
	float kAirResistance;
	float kWaterResistance;
	float accThrust;
	float accLift;
	int surface_idx;
	Vec3 wspin;
	Vec3 gravity;
	Vec3 waterGravity;
	Vec3 normal;
	Vec3 rollAxis;
	Quat_tpl<float> q0;
	float minBounceVel;
	float minVel;
	IPhysicalEntity* pColliderToIgnore;
	int iPierceability;
	int collTypes;
	int areaCheckPeriod;
};

struct SKillZoneParams
{
	float damageTimeout;
	float lifetime;
	float damage;
	const char* explosionEffect;
	float radius;
	float delay;
	float attenuationTime;
	float wallAttenuationTime;
	const char* effect;
	const char* wallEffect;
};

struct SScaledEffectParams
{
	const char* ppname;
	float radius;
	float fadeInTime;
	float fadeOutTime;
	float maxValue;
	float aiObstructionRadius;
	float smokeEffectCoef;
	float smokeEffectHeight;
	Vec3 colorCenter;
	Vec3 colorEdge;
	Vec3 smokeEffectOffset;
	float smokeMaskEyeDirectionOffset;
	float lifetime;
};

struct SCollisionParams
{
	char pad_0x0008[0x8];
	const char* effectName;
	const char* sound;
	float scale;
};

struct SExplosionParams
{
	float minRadius;
	float maxRadius;
	float minPhysRadius;
	float maxPhysRadius;
	float pressure;
	float holeSize;
	float terrainHoleSize;
	char pad_0x0028[0x28];
	const char* effectName;
	const char* effectClass;
	float effectScale;
	float maxblurdist;
	float shakeMinR;
	float shakeMaxR;
	float shakeScale;
	float shakeRnd;
	const char* deactivatedEffectName;
	char pad_0x0058[0x58];
};

struct SFlashbangInfo
{
	float blindAmount;
	float blindAmountYellowCoef;
	float blindAmountGreenCoef;
	float flashbangBaseTime;
	float rayCoef;
	float upRayLength;
	float sideRayLength;
	float reflectionAngle;
	float flashRedZoneAngle;
	float flashYellowZoneAngle;
};

struct SFlashbangParams
{
	float maxRadius;
	SFlashbangInfo flashInfo;
};

const struct SAmmoParam
{
	unsigned int flags;
	int serverSpawn;
	int predictSpawn;
	float lifetime;
	bool isAnimated;
	float showtime;
	float acceltime;
	unsigned __int16 aiType;
	EAmmoKind ammoKind;
	int bulletType;
	CryStringT hitType;
	int hitPoints;
	bool noBulletHits;
	bool quietRemoval;
	float sleepTime;
	bool can_toss;
	int toss_priority;
	float damage;
	ELaunchType launch_type;
	CryStringT netPolicy;
	int maxProjectileCount;
	float targetCloseDist;
	float targetFarDist;
	bool canBeDeactivated;
	EPhysicalizationType physicalizationType;
	float mass;
	float speed;
	float maxSpeed;
	int maxLoggedCollisions;
	int traceable;
	Vec3 spin;
	Vec3 spinRandom;
	float turnSpeed;
	float oscillationAmplitude;
	float oscillationFrequency;
	const char* surfaceTypeName;
	unsigned __int16 surfaceTypeID;
	std::unique_ptr<pe_params_particle, std::default_delete<pe_params_particle> > pParticleParams;
	const char* fpGeometryName;
	std::unique_ptr<SKillZoneParams, std::default_delete<SKillZoneParams> > pKillzoneParams;
	char pad_0x0128[0x128];
	std::unique_ptr<SScaledEffectParams, std::default_delete<SScaledEffectParams> > pScaledEffect;
	std::unique_ptr<SCollisionParams, std::default_delete<SCollisionParams> > pCollision;
	std::unique_ptr<SExplosionParams, std::default_delete<SExplosionParams> > pExplosion;
	std::unique_ptr<SFlashbangParams, std::default_delete<SFlashbangParams> > pFlashbang;
	CEntityClass* pEntityClass;
};
