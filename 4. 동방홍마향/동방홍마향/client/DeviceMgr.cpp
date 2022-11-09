#include "stdafx.h"
#include "DeviceMgr.h"

IMPLEMENT_SINGLETON(CDeviceMgr)

CDeviceMgr::CDeviceMgr()
{
}


CDeviceMgr::~CDeviceMgr()
{
	Release();
}

LPDIRECT3DDEVICE9 CDeviceMgr::GetDevice() const
{
	return m_pGraphicDev;
}

LPD3DXSPRITE CDeviceMgr::GetSprite() const
{
	return m_pSprite;
}

HRESULT CDeviceMgr::InitDevice(HWND hWnd, const DWORD & dwWinCX, const DWORD & dwWinCY, MODE eMode)
{
	HRESULT hr = 0;
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 Caps;
	ZeroMemory(&Caps, sizeof(D3DCAPS9));

	hr = m_pSDK->GetDeviceCaps(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed", E_FAIL);

	DWORD vp = 0;

	if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = dwWinCX;	// 후면버퍼 가로크기
	d3dpp.BackBufferHeight = dwWinCY;	// 후면버퍼 세로크기
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 후면버퍼 픽셀포맷
	d3dpp.BackBufferCount = 1;	// 후면버퍼 개수

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; // 멀티샘플링 안씀.
	d3dpp.MultiSampleQuality = 0;

	// 렌더링 방식
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // 스왑체인 방식.
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = eMode;	// TRUE 창모드, FALSE 전체화면모드.
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, vp, &d3dpp, &m_pGraphicDev);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);

	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);

	return S_OK;
}

void CDeviceMgr::Render_Begin()
{
	m_pGraphicDev->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	m_pGraphicDev->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End()
{
	m_pSprite->End();
	m_pGraphicDev->EndScene();

	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void CDeviceMgr::Release()
{
	if (SafeRelease(m_pSprite))
		ERR_MSG(L"m_pSprite Release Failed");

	if (SafeRelease(m_pGraphicDev))
		ERR_MSG(L"m_pGraphicDev Release Failed");

	if (SafeRelease(m_pSDK))
		ERR_MSG(L"m_pSDK Release Failed");
}
