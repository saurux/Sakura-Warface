#pragma once

#include <SDK/Math/Math.h>

struct WorldToScreenData
{
	float PositionX;
	float PositionY;
	float PositionZ;
	float* ScreenX;
	float* ScreenY;
	float* ScreenZ;
};

template <typename T>
struct Plane_tpl {
    Vec3_tpl<T> n;
    T d;
};

class CCamera {
public:
    struct ScissorInfo {

        unsigned __int16 x1;
        unsigned __int16 y1;
        unsigned __int16 x2;
        unsigned __int16 y2;
    };

public:
    Matrix34_tpl<float> m_Matrix;
    float m_fov;
    int m_Width;
    int m_Height;
    float m_ProjectionRatio;
    float m_PixelAspectRatio;
    Vec3_tpl<float> m_edge_nlt;
    Vec3_tpl<float> m_edge_plt;
    Vec3_tpl<float> m_edge_flt;
    float m_asymL;
    float m_asymR;
    float m_asymB;
    float m_asymT;
    Vec3_tpl<float> m_cltp;
    Vec3_tpl<float> m_crtp;
    Vec3_tpl<float> m_clbp;
    Vec3_tpl<float> m_crbp;
    Vec3_tpl<float> m_cltn;
    Vec3_tpl<float> m_crtn;
    Vec3_tpl<float> m_clbn;
    Vec3_tpl<float> m_crbn;
    Vec3_tpl<float> m_cltf;
    Vec3_tpl<float> m_crtf;
    Vec3_tpl<float> m_clbf;
    Vec3_tpl<float> m_crbf;
    Plane_tpl<float> m_fp[6];
    unsigned int m_idx1[6];
    unsigned int m_idy1[6];
    unsigned int m_idz1[6];
    unsigned int m_idx2[6];
    unsigned int m_idy2[6];
    unsigned int m_idz2[6];
    float m_zrangeMin;
    float m_zrangeMax;
    int m_nPosX;
    int m_nPosY;
    int m_nSizeX;
    int m_nSizeY;
    struct IVisArea* m_pPortal;
    ScissorInfo m_ScissorInfo;
    void* m_pMultiCamera;
    Vec3_tpl<float> m_OccPosition;
    int m_JustActivated;
};

class CRenderer
{
public:
	char pad_0x14C878[0x14C878];
	int m_desktopWidth;
	char pad_0x14C87C[0x14C87C];
	int m_desktopHeight;
	char pad_0x14CA80[0x14CC70];
	struct IDXGISwapChain* m_pSwapChain; //0x14CA80 

	// 0x14CCC8
	/*
	*(_DWORD *)(v1 + 1364252) = *(_DWORD *)(sub_1410169A0() + 112);
	  v3 = sub_141016010();
	  v4 = *(_QWORD *)(v1 + 1363416);
	  *(_QWORD *)(v1 + 0x14D000) = v3;
	*/
    CRenderer* GetThis() { return this; }

    // 0x14CB80
	IDXGISwapChain* GetSwapChain() { return *(IDXGISwapChain**)((uintptr_t)this + 0x14CF00); } // string "CD3D9Renderer::m_DynVB[%d] Verts:%d VertSize:%d" - xref to one 47 line
    CCamera* SetGetCamera(const CCamera* pCamera, bool bSet) {
        return VirtualFunction<CCamera*(__thiscall*)(void*, const CCamera*, bool)>(this, 68)(this, pCamera, bSet);
    }
    Vec3 GetViewCamera() {
        CCamera pCamera;
        CCamera* pNCamera = SetGetCamera(&pCamera, false);
        return pNCamera->m_Matrix.GetTranslation();
    }

    /*
    * 0x1740 - ����
    * 0x17D0
    * 0x17F0
	Vector3 dwCamera; //0x17D0
	Vector3 PersonCamera; //0x17E0
	Vector3 vPersonCamera; //0x17EC
	Vector3 pCamera; //0x17F8
    */
    Vec3 GetViewCamera2() { return *(Vec3*)((uintptr_t)this + 0x17D0); } // Deleting Render meshes, render resource

	bool ProjectToScreen(WorldToScreenData* info) { return VirtualFunction<bool(__thiscall*)(void*, WorldToScreenData*)>(this, 0x380 / 8)(this, info); }

	float GetWidth() { return (float)VirtualFunction<int(__thiscall*)(void*)>(this, 102)(this); }
	float GetHeight() { return (float)VirtualFunction<int(__thiscall*)(void*)>(this, 103)(this); }
    
    template <typename T>
    void SetPostEffectParam(const char* pParam, T tValue) { VirtualFunction<T(__fastcall*)(void*, const char*, T)>(this, 0x660 / 8)(this, pParam, tValue); }

	bool WorldToScreen(Vec3 vEntPos, Vec3* sPos)
	{
		WorldToScreenData info;
		info.PositionX = vEntPos.x;
		info.PositionY = vEntPos.y;
		info.PositionZ = vEntPos.z;

		info.ScreenX = &sPos->x;
		info.ScreenY = &sPos->y;
		info.ScreenZ = &sPos->z;

		this->ProjectToScreen(&info);

		if (sPos->z < 0.0f || sPos->z > 1.0f)
		{
			return 0;
		}

		sPos->x *= (this->GetWidth() / 100.0f);
		sPos->y *= (this->GetHeight() / 100.0f);
		sPos->z *= 1.0f;

		return (sPos->z < 1.0f);
	}
};
