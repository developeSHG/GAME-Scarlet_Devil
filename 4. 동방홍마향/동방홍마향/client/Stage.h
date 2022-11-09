#pragma once
#include "Scene.h"

class CTestObj;

class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	D3DXMATRIX m_matWorld;
};

