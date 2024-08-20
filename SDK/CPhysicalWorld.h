#pragma once

enum EPhysicsForeignIds
{
	PHYS_FOREIGN_ID_TERRAIN = 0x0,
	PHYS_FOREIGN_ID_STATIC = 0x1,
	PHYS_FOREIGN_ID_ENTITY = 0x2,
	PHYS_FOREIGN_ID_FOLIAGE = 0x3,
	PHYS_FOREIGN_ID_ROPE = 0x4,
	PHYS_FOREIGN_ID_SOUND_OBSTRUCTION = 0x5,
	PHYS_FOREIGN_ID_SOUND_PROXY_OBSTRUCTION = 0x6,
	PHYS_FOREIGN_ID_SOUND_REVERB_OBSTRUCTION = 0x7,
	PHYS_FOREIGN_ID_WATERVOLUME = 0x8,
	PHYS_FOREIGN_ID_USER = 0x64,
};


class IPhysicalEntity
{
public:
	void* GetForeignData(EPhysicsForeignIds itype)
	{
		return VirtualFunction<void* (__thiscall*)(void*, EPhysicsForeignIds)>(this, 0x68 / 8)(this, itype);
	}

	int GetiForeignData()
	{
		return VirtualFunction<int (__thiscall*)(void*)>(this, 112 / 8)(this);
	}
};

struct ray_hit
{
public:
	float dist;
	IPhysicalEntity* pCollider;
	int ipart;
	int partid;
	short surface_idx;
	short idmatOrg;	// original material index, not mapped with material mapping
	int foreignIdx;
	int iNode; // BV tree node that had the intersection; can be used for "warm start" next time
	Vec3 pt;
	Vec3 n;	// surface normal
	int bTerrain;	// global terrain hit
	int iPrim; // hit triangle index
	ray_hit* next; // reserved for internal use, do not change
};

struct ray_hit_cached
{	// used in conjunction with rwi_reuse_last_hit
public:
	ray_hit_cached() { pCollider = 0; ipart = 0; }
	ray_hit_cached(const ray_hit& hit) { pCollider = hit.pCollider; ipart = hit.ipart; iNode = hit.iNode; }
	ray_hit_cached& operator=(const ray_hit& hit) { pCollider = hit.pCollider; ipart = hit.ipart; iNode = hit.iNode; return *this; }

	IPhysicalEntity* pCollider;
	int ipart;
	int iNode;
};

/*
struct pe_params_pos : pe_params
{
	Vec3 pos;
	Quat_tpl<float> q;
	float scale;
	Matrix34* pMtx3x4;
	Matrix33_tpl<float>* pMtx3x3;
	int iSimClass;
	int bRecalcBounds;
	bool bEntGridUseOBB;
};
*/

struct WriteLockCond
{
	volatile int* prw;
	int iActive;
};

struct geom_contact_area
{
	int type;
	int npt;
	int nmaxpt;
	float minedge;
	int* piPrim[2];
	int* piFeature[2];
	Vec3* pt;
	Vec3 n1;
};

struct geom_contact
{
	long double t;
	Vec3 pt;
	Vec3 n;
	Vec3 dir;
	int iUnprojMode;
	float vel;
	int id[2];
	int iPrim[2];
	int iFeature[2];
	int iNode[2];
	Vec3* ptborder;
	int(*idxborder)[2];
	int nborderpt;
	int bClosed;
	Vec3 center;
	bool bBorderConsecutive;
	geom_contact_area* parea;
};

struct intersection_params
{
	int iUnprojectionMode;
	Vec3 centerOfRotation;
	Vec3 axisOfRotation;
	float time_interval;
	float vrel_min;
	float maxSurfaceGapAngle;
	float minAxisDist;
	Vec3 unprojectionPlaneNormal;
	Vec3 axisContactNormal;
	float maxUnproj;
	Vec3 ptOutsidePivot[2];
	bool bSweepTest;
	bool bKeepPrevContacts;
	bool bStopAtFirstTri;
	bool bNoAreaContacts;
	bool bNoBorder;
	int bExactBorder;
	int bNoIntersection;
	int bBothConvex;
	int bThreadSafe;
	int bThreadSafeMesh;
	geom_contact* pGlobalContacts;
};

struct SCollisionClass
{
	unsigned int type;
	unsigned int ignore;
};

struct EventPhysRWIResult;

struct SRWIParams
{
public:
	void* pForeignData;
	int iForeignData;
	int (*OnEvent)(const EventPhysRWIResult*);
	Vec3 org;
	Vec3 dir;
	int objtypes;
	unsigned int flags;
	ray_hit* hits;
	int nMaxHits;
	ray_hit_cached* phitLast;
	int nSkipEnts;
	IPhysicalEntity** pSkipEnts;
};

/*
enum rwi_flags
{
	rwi_ignore_terrain_holes = 0x20,
	rwi_ignore_noncolliding = 0x40,
	rwi_ignore_back_faces = 0x80,
	rwi_ignore_solid_back_faces = 0x100,
	rwi_pierceability_mask = 0xF,
	rwi_pierceability0 = 0x0,
	rwi_stop_at_pierceable = 0xF,
	rwi_separate_important_hits = 0x200,
	rwi_colltype_bit = 0x10,
	rwi_colltype_any = 0x400,
	rwi_queue = 0x800,
	rwi_force_pierceable_noncoll = 0x1000,
	rwi_debug_trace = 0x2000,
	rwi_update_last_hit = 0x4000,
	rwi_any_hit = 0x8000,
};
*/

enum geom_flags
{
	geom_colltype0 = 0x1,
	geom_colltype1 = 0x2,
	geom_colltype2 = 0x4,
	geom_colltype3 = 0x8,
	geom_colltype4 = 0x10,
	geom_colltype5 = 0x20,
	geom_colltype6 = 0x40,
	geom_colltype7 = 0x80,
	geom_colltype8 = 0x100,
	geom_colltype9 = 0x200,
	geom_colltype10 = 0x400,
	geom_colltype11 = 0x800,
	geom_colltype12 = 0x1000,
	geom_colltype13 = 0x2000,
	geom_colltype14 = 0x4000,
	geom_colltype_ray = 0x8000,
	geom_floats = 0x10000,
	geom_proxy = 0x20000,
	geom_structure_changes = 0x40000,
	geom_can_modify = 0x80000,
	geom_squashy = 0x100000,
	geom_log_interactions = 0x200000,
	geom_monitor_contacts = 0x400000,
	geom_manually_breakable = 0x800000,
	geom_no_coll_response = 0x1000000,
	geom_mat_substitutor = 0x2000000,
	geom_break_approximation = 0x4000000,
	geom_no_particle_impulse = 0x8000000,
	geom_destroyed_on_break = 0x2000000,
	geom_colltype_player = 0x2,
	geom_colltype_explosion = 0x4,
	geom_colltype_vehicle = 0x8,
	geom_colltype_foliage = 0x10,
	geom_colltype_debris = 0x20,
	geom_colltype_foliage_proxy = 0x2000,
	geom_colltype_obstruct = 0x4000,
	geom_colltype_solid = 0xFFB,
	geom_collides = 0xFFFF,
};

enum pe_collision_class
{
	collision_class_terrain = 0x1,
	collision_class_wheeled = 0x2,
	collision_class_living = 0x4,
	collision_class_articulated = 0x8,
	collision_class_soft = 0x10,
	collision_class_rope = 0x20,
	collision_class_particle = 0x40,
	collision_class_game = 0x400,
	collision_class_player = 0x800,
	collision_class_ai = 0x1000,
	collision_class_death_capsule = 0x2000,
	collision_class_safe_capsule = 0x4000,
	collision_class_ragdoll_player = 0x8000,
	collision_class_ragdoll_ai = 0x10000,
	collision_class_smoke = 0x20000,
};


class CPhysicalWorld
{
public:
	int RayTrace(SRWIParams& rp, const char* pNameTag, int iCaller)
	{
		return VirtualFunction<int(__thiscall*)(void*, SRWIParams&, const char*, int)>(this, 280 / 8)(this, rp, pNameTag, iCaller);
	}

	//int RayTraceEntity(IPhysicalEntity* pient, Vec3* origin, Vec3* dir, ray_hit* pHit, pe_params_pos* pp, unsigned int geomFlagsAn)
	//{
		//return VirtualFunction<int(__thiscall*)(void*, IPhysicalEntity*, Vec3*, Vec3*, ray_hit*, pe_params_pos*, unsigned int)>(this, 440 / 8)(this, pient, origin, dir, pHit, pp, geomFlagsAn);
	//}

	int RayWorldIntersection(const Vec3& org, const Vec3& dir, int objtypes, unsigned int flags, ray_hit* hits, int nmaxhits, IPhysicalEntity** pSkipEnts = 0, int nSkipEnts = 0, void* pForeignData = 0, int iForeignData = 0, const char* pNameTag = "", ray_hit_cached* phitLast = 0, int iCaller = 4)
	{
		SRWIParams rp;
		rp.org = org;
		rp.dir = dir;
		rp.objtypes = objtypes;
		rp.flags = flags;
		rp.hits = hits;
		rp.nMaxHits = nmaxhits;
		rp.pForeignData = pForeignData;
		rp.iForeignData = iForeignData;
		rp.phitLast = phitLast;
		rp.pSkipEnts = pSkipEnts;
		rp.nSkipEnts = nSkipEnts;

		return this->RayTrace(rp, pNameTag, iCaller);
	}

	int RayWorldIntersectionSafe(const Vec3& org, const Vec3& dir, int objtypes, unsigned int flags, ray_hit* hits, int nMaxHits, IPhysicalEntity** pSkipEnts = 0, int nSkipEnts = 0, void* pForeignData = 0, int iForeignData = 0, const char* pNameTag = "RayWorldIntersection(Game)", ray_hit_cached* phitLast = 0, int iCaller = 4)
	{
		return VirtualFunction<int(__fastcall*)(PVOID, const Vec3&, const Vec3&, int, unsigned int, ray_hit*, int, IPhysicalEntity**, int, void*, int, const char*, ray_hit_cached*, int)>(this, 776 / 8)(this, org, dir, objtypes, flags, hits, nMaxHits, pSkipEnts, nSkipEnts, pForeignData, iForeignData, pNameTag, phitLast, iCaller);
	}

	Vec3 GetMPos(Vec3 vCameraPosition, Vec3 vBonePosition, FLOAT Correct)
	{
		Vec3 vOut = vBonePosition - vCameraPosition;
		FLOAT sqr = (FLOAT)sqrt(vOut.x * vOut.x + vOut.y * vOut.y + vOut.z * vOut.z);
		vOut /= sqr;
		vOut *= sqr - Correct;
		return vOut;
	}

	BOOL EntityIsVisible(Vec3 vCameraPosition, Vec3 vBonePosition, FLOAT Correct)
	{
		ray_hit tmpHit;
		Vec3 vOut(GetMPos(vCameraPosition, vBonePosition, Correct));
		return !this->RayWorldIntersection(vCameraPosition, vOut, 0x100 | 1, 0xA | 0x400  | 0xA0001500, &tmpHit, 1);
	}

	bool IsVisible(Vec3 shootPos, Vec3 pos)
	{
		ray_hit tmpHit;
		return !this->RayWorldIntersection(shootPos, pos - shootPos, 0x100 | 1, 0xA | 0x400, &tmpHit, 1);
	}

	bool IsVisibleSafe(Vec3 shootPos, Vec3 pos, IPhysicalEntity** pSkipEnts = 0, int nSkipEnts = 0, int pierceability = 10) 
	{
		ray_hit rayhit;
		return !this->RayWorldIntersectionSafe(shootPos, pos - shootPos, ent_static | ent_terrain, 0xA0001500 | pierceability, &rayhit, 1, pSkipEnts, nSkipEnts);
	}

	bool IsVisibleInSmoke(Vec3 shootPos, Vec3 pos)
	{
		ray_hit tmpHit;
		return !this->RayWorldIntersection(shootPos, pos - shootPos, 0x100 | 1, 0xA | 0x400 | 0xA0001500, &tmpHit, 1);
	}
};