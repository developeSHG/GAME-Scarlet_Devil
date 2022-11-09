#pragma once
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
private:
	CSceneMgr();
	~CSceneMgr();
public:
	enum SCENEID { SCENE_LOGO, SCENE_INTRO, SCENE_STAGE, SCENE_END };
public:
	SCENEID Get_SceneID() { return m_eCurScene; }
public:
	void SceneChange(SCENEID eSceneID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	CScene* m_pScene;
	SCENEID m_eCurScene;
	SCENEID m_eNextScene;
};

