#pragma once

enum EBombState
{
	eBS_Unknown = 0x0,
	eBS_Initial = 0x1,
	eBS_Dropped = 0x2,
	eBS_PickedUp = 0x3,
	eBS_Planted = 0x4,
	eBS_Exploded = 0x5,
	eBS_Defusing = 0x6,
	eBS_Count = 0x7,
};

enum EPlantSite
{
	ePlantSite_Unknown = 0x0,
	ePlantSite_A = 0x1,
	ePlantSite_B = 0x2,
	ePlantSite_Count = 0x3,
};

class PTBGameRules
{
public:
	DWORD64 m_bombExplosionTime;
	EBombState m_bombState;
	EPlantSite m_plantSite;
	EntityId m_bombOwner;
};