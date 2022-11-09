#pragma once
class CDeviceMgr
{
	DECLARE_SINGLETON(CDeviceMgr)
public:
	enum MODE { MODE_FULL, MODE_WIN };
private:
	CDeviceMgr();
	~CDeviceMgr();

public:
	LPDIRECT3DDEVICE9 GetDevice() const;
	LPD3DXSPRITE GetSprite() const;

public:
	HRESULT InitDevice(
		HWND hWnd, const DWORD& dwWinCX,
		const DWORD& dwWInCY, MODE eMode);
	void Render_Begin();
	void Render_End();
	void Release();

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	LPD3DXSPRITE		m_pSprite;

};

