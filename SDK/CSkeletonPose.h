#pragma once

class CAnimationGraphState {
public:
    const char* GetCurrentStateName() { return VirtualFunction<const char*(__thiscall*)(void*)>(this, 32)(this); }

    char pad_0x0000[0x18]; //0x0000
    unsigned __int32 m_layerIndex; //0x0018 
    char pad_0x001C[0xC]; //0x001C
    class CAnimationGraph* m_pGraph; //0x0028 

}; //Size=0x0030

class CSkeletonPose
{
public:
	QuatT& GetAbsJointByID(int nJointID) { return VirtualFunction<QuatT& (__thiscall*)(void*, int)>(this, 0x38 / 8)(this, nJointID); }
	short GetJointIdByName(const char* sz_joint_name) { return VirtualFunction<short(__fastcall*)(PVOID64, const char*)>(this, 24 / 8)(this, sz_joint_name); }
};