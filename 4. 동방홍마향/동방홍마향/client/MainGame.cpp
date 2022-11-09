#include "stdafx.h"
#include "MainGame.h"
#include "KeyMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	
	HRESULT hr = 0;
	hr = CDeviceMgr::GetInstance()->InitDevice(g_hWND, WINCX, WINCY, CDeviceMgr::MODE_WIN);
	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EnemyUI/Enemy_UI.png", L"Enemy_UI");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EnemyUI/EnemyHp_UI.png", L"EnemyHp_UI");
}

void CMainGame::Update()
{
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	CDeviceMgr::GetInstance()->Render_Begin();
	CSceneMgr::GetInstance()->Render();
	CDeviceMgr::GetInstance()->Render_End();
}

void CMainGame::Release()
{
	CKeyMgr::DestroyInstance();
	CTextureMgr::DestroyInstance();
	CObjMgr::DestroyInstance();
	CSceneMgr::DestroyInstance();
	CDeviceMgr::DestroyInstance();
}
