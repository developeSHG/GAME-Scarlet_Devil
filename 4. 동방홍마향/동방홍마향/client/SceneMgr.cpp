#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Stage.h"
IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eSceneID)
{
	m_eNextScene = eSceneID;
	if (m_eCurScene != m_eNextScene)
	{
		if (m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		switch (m_eNextScene)
		{
		case SCENEID::SCENE_LOGO:
			break;
		case SCENEID::SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case SCENEID::SCENE_END:
			break;
		}
		m_pScene->Initialize();
		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}
