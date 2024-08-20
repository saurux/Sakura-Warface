#pragma once

#include <SDK/CRenderer.h>

class CSystem
{
public:
	bool Update(CSystem* pSystem, int updateFlags, int nPauseMode)
	{
		VirtualFunction<bool(__thiscall*)(void*, int, int)>(this, 4)(this, updateFlags, nPauseMode);
	}

	CCamera* GetViewCamera() { return VirtualFunction<CCamera*(__thiscall*)(void*)>(this, 936 / 8)(this); }

	Vec3 GetCameraPos() {
		CCamera* pCamera = this->GetViewCamera();
		return pCamera->m_Matrix.GetTranslation();
	}
};