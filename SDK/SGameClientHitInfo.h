#pragma once
#include "CActor.h"


struct SGameClientHitInfo
{
	EntityId shooterId;//0x00
	EntityId targetId;//0x04
	int material;//0x08
	int typeId;//0x0C
	int bulletType;//0x10
	int partId;//0x14
	Vec3 pos;//0x18
	Vec3 dir;//0x24
	Vec3 shootPos;//0x30
	bool meleeArmorAbsorb;//0x3C
	EntityId itemId;////0x40
	EntityId projectileId;//0x44
	uint16 ammoClassId;//0x48
	float angle;//0x4C
	Vec3 normal;//0x50
	bool silencer;//0x5C
	float travelDistance;//0x60
	float damageReduction;//0x64
	bool bFromRemote;//0x68
	bool canBeReported;//0x69
	bool bRequest;//0x6A
};

struct SSharedGameHitInfo
{
	unsigned int shooterId; // 0x0
	unsigned int targetId; // 0x4
	int material; // 0x8
	int typeId; // 0x10
	int bulletType; // 0xC
	int partId; // 0x14
	Vec3 pos; // 0x18
	Vec3 dir; // 0x24
	Vec3 shootPos; // 0x30
	bool meleeArmorAbsorb;
};

struct SSourceGameHitInfo
{
	int weaponGameObjectId;
	unsigned int projectileId;
	unsigned __int16 ammoClassId;
	float angle;
	Vec3 normal;
	// DWORD64 hitTime;
	bool silencer;
};

struct SClientGameHitInfo
{
	SSharedGameHitInfo shared;
	SSourceGameHitInfo source;
	float travelDistance;
	float damageReduction;
	float timeStamp;
	__int16 bFromRemote;
	bool canBeReported;
};

struct SGameServertHitInfo
{
	EntityId shooterId;//0x00
	EntityId targetId;//0x04
	int material;//0x08
	int typeId;//0x0C
	int bulletType;//0x10
	int partId;//0x14
	Vec3 pos;//0x18
	Vec3 dir;//0x24
	Vec3 shootPos;//0x30
	bool meleeArmorAbsorb;//0x3C
	EntityId itemId;////0x40
	EntityId projectileId;//0x44
	uint16 ammoClassId;//0x48
	float angle;//0x4C
	Vec3 normal;//0x50
	bool silencer;//0x5C
	float travelDistance;//0x60
	float damageReduction;//0x64
	bool bFromRemote;//0x68
	bool canBeReported;//0x69
	bool bRequest;//0x6A
};

struct SNetHitInfo
{
	SNetHitInfo(EntityId targetId, int material, int type, int partId, Vec3 pos, float damageReduction, BYTE profilerId)
		: targetId(targetId), material(material), typeId(type), partId(partId), pos(pos), damageReduction(damageReduction), profilerId(profilerId) {}
	EntityId targetId; // 0x00
	int material; // 0x04
	int typeId; // 0x08
	int partId; // 0x0C
	Vec3 pos; // 0x10
	float damageReduction; // 0x1C
	BYTE profilerId; // 0x20
};

struct SShootInfo
{
	SShootInfo(EntityId projectileId, std::vector<SNetHitInfo> hits) : projectileId(projectileId), hits(hits) {}
	EntityId projectileId;  // 0x00
	std::vector<SNetHitInfo> hits; // 0x08
};

struct SRequestShootHit
{
	Vec3 shootPos;  // 0x00
	int predictionHandle; // 0x0C
	Vec3 dir; // 0x10
	BYTE profilerId; // 0x1C
	std::vector<SShootInfo> shoots; // 0x20
	EntityId shooterId; // 0x38
	EntityId itemId; // 0x3C
};

struct SGameClientShootHitInfo
{
	EntityId shooterId;
	EntityId targetId;
	Vec3 vPosition;
	Vec3 vDir;
	Vec3 vShootPosition;
	int typeId;
	int materialId;

	SGameClientShootHitInfo(EntityId shooterId, EntityId targetId,
		Vec3 vPosition, Vec3 vDir, Vec3 vShootPosition, int typeId, int materialId)
		: shooterId(shooterId), targetId(targetId), vPosition(vPosition), vDir(vDir), vShootPosition(vShootPosition), typeId(typeId),
		materialId(materialId) {
	}

};

struct SClientHitInfo
{
	SClientHitInfo(EntityId targetId, int material, int type, int partId, Vec3 pos, float damageReduction, BYTE profilerId)
		: targetId(targetId), material(material), typeId(type), partId(partId), pos(pos), damageReduction(damageReduction), profilerId(profilerId) {}
	EntityId targetId; // 0x00
	int material; // 0x04
	int typeId; // 0x08
	int partId; // 0x0C
	Vec3 pos; // 0x10
	float damageReduction; // 0x1C
	BYTE profilerId; // 0x20
};

struct SShootClientInfo
{
	SShootClientInfo(EntityId projectileId, std::vector<SClientHitInfo> hits) : projectileId(projectileId), hits(hits) {}
	EntityId projectileId;  // 0x00
	std::vector<SClientHitInfo> hits; // 0x08
};

struct SServerHitInfo
{
	Vec3 shootPos;  // 0x00
	int predictionHandle; // 0x0C
	Vec3 dir; // 0x10
	BYTE profilerId; // 0x1C
	std::vector<SShootClientInfo> shoots; // 0x20
	EntityId shooterId; // 0x38
	EntityId itemId; // 0x3C
};

struct SvRequestHitParams
{
	unsigned int shooterId;
	unsigned int targetId;
	int material;
	int typeId;
	int partId;
	Vec3 pos;
	Vec3 dir;
	Vec3 shootPos;
	unsigned int shooterCommand;
	unsigned int targetCommand;
	unsigned int projectileId;
	float travelDistance;
	float damageReduction;
	float timeStamp;
};

struct SSharedParams
{
	EntityId targetId; // 0x00
	int material; // 0x04
	int typeId; // 0x08
	int partId; // 0x0C
	Vec3 pos; // 0x10
	float damageReduction; // 0x1C
	BYTE profilerId; // 0x20
};

struct SShootInfoParams
{
	EntityId projectileId;  // 0x00
	SSharedParams hits; // 0x08
};

struct SShootParams
{
	unsigned int shooterId;
	unsigned int targetId;
	int material;
	int typeId;
	int partId;
	Vec3 pos;
	Vec3 dir;
	Vec3 shootPos;
	unsigned int shooterCommand;
	unsigned int targetCommand;
	unsigned int projectileId;
	float travelDistance;
	float damageReduction;
	float timeStamp;
};

struct SHitInfo
{
	SHitInfo(EntityId targetId, int material, int type, int partId, Vec3 pos, float damageReduction, BYTE targetCommand)
		: targetId(targetId), material(material), typeId(type), partId(partId), pos(pos), damageReduction(damageReduction), targetCommand(targetCommand) {}
	EntityId targetId; // 0x00
	int material; // 0x04
	int typeId; // 0x08
	int partId; // 0x0C
	Vec3 pos; // 0x10
	float damageReduction; // 0x1C
	BYTE targetCommand; // 0x20
};

struct SRequestInfo
{
	SRequestInfo(EntityId projectileId, std::vector<SHitInfo> hits) : projectileId(projectileId), hits(hits) {}
	EntityId projectileId;  // 0x00
	std::vector<SHitInfo> hits; // 0x08
};

struct SShootHitInfo
{
	Vec3 shootPos;  // 0x00
	int predictionHandle; // 0x0C
	Vec3 dir; // 0x10
	BYTE shooterCommand; // 0x1C
	std::vector<SRequestInfo> shoots; // 0x20
	EntityId shooterId; // 0x38
	EntityId itemId; // 0x3C
};
