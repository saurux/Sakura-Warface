#pragma once
#include <Hook/vmthook.h>
#include <Render/Imgui.hpp>

#define STB_IMAGE_IMPLEMENTATION

/*
struct PlayerClass
{
	int SniperX = 0;
	int SniperY = 0;
	ID3D11ShaderResourceView* SniperImage = NULL;

	int MedicX = 0;
	int MedicY = 0;
	ID3D11ShaderResourceView* MedicImage = NULL;

	int RiflemanX = 0;
	int RiflemanY = 0;
	ID3D11ShaderResourceView* RiflemanImage = NULL;

	int EngineerX = 0;
	int EngineerY = 0;
	ID3D11ShaderResourceView* EngineerImage = NULL;
}Player;

struct Bones {
	const char* Head = "Bip01 Head";
	const char* Neck = "Bip01 Neck";
	const char* Spine = "Bip01 Spine";
	const char* lShoulder = "Bip01 L UpperArm";
	const char* rShoulder = "Bip01 R UpperArm";
	const char* lForeTwist = "Bip01 L ForeTwist";
	const char* rForeTwist = "Bip01 R ForeTwist";
	const char* lForeArm = "Bip01 L ForeArm";
	const char* rForeArm = "Bip01 R ForeArm";
	const char* lHand = "Bip01 L Hand";
	const char* rHand = "Bip01 R Hand";
}Bones;
*/

CMenu* pMenu = new CMenu();

//#pragma region hooks
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
Present oPresent;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//VMTHookManager* pSwapChainHook = new VMTHookManager();
//#pragma endregion

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(pMenu->oWndProc, hWnd, uMsg, wParam, lParam);
}

bool bInit = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!bInit)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pMenu->pDevice)))
		{
			pMenu->pDevice->GetImmediateContext(&pMenu->pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			pMenu->hWnd = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pMenu->pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pMenu->pRenderTargetView);
			pMenu->oWndProc = (WNDPROC)SetWindowLongPtr(pMenu->hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
			pBackBuffer->Release();
			pMenu->UIInit();
			//InitImGui();
			bInit = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Renderer

	pMenu->UI(); // Main Menu

	ImGui::Render();

	pMenu->pContext->OMSetRenderTargets(1, &pMenu->pRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	return oPresent(pSwapChain, SyncInterval, Flags);
}

using pResizeBuffers = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
pResizeBuffers oResizeBuffers;
HRESULT hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (pMenu->pRenderTargetView) {
		pMenu->pContext->OMSetRenderTargets(0, 0, 0);
		pMenu->pRenderTargetView->Release();
	}

	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	// Perform error handling here!

	pMenu->pDevice->CreateRenderTargetView(pBuffer, NULL, &pMenu->pRenderTargetView);
	// Perform error handling here!
	pBuffer->Release();

	pMenu->pContext->OMSetRenderTargets(1, &pMenu->pRenderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pMenu->pContext->RSSetViewports(1, &vp);
	//ScreenX = SSystemGlobalEnvironment::Singleton()->GetRenderer()->GetWidth();
	//ScreenY = SSystemGlobalEnvironment::Singleton()->GetRenderer()->GetHeight();
	//ScreenCenterX = ScreenX / 2;
	//ScreenCenterY = ScreenY / 2;
	return hr;
}



