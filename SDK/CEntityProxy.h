#pragma once

class CEntityProxy
{
private:
	char pad_0x0000[0x24]; //0x0000
	__int32 dwRenderFlags; //0x0024 
public:
	void SetRenderFlags(__int32 flag = 0x80018) { *(__int32*)((uint64_t)this + 0x24) = flag;}
	void SetHUDSilhouettesParam(float a, float r, float g, float b) { return VirtualFunction<void(__thiscall*)(void*, float, float, float, float)>(this, 352 / 8)(this, a / 255, r / 255, g / 255, b / 255); }
};