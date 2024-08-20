#pragma once

#include "CSkeletonPose.h"

class CCharacterInstance
{
public:
	CSkeletonPose* GetSkeletonPose() { return VirtualFunction<CSkeletonPose*(__thiscall*)(void*)>(this, 0x28 / 8)(this); }
	void SetAnimationSpeed(float speed) { VirtualFunction<void(__thiscall*)(void*, float)>(this, 384 / 8)(this, speed); }
};