#include "stdafx.h"
#include "Mouse.h"
#include "PointCollider.h"

namespace kfgd
{

	CMouse::CMouse()
		: m_pCollider(nullptr)
	{
		m_pCollider = new CPointCollider;
		m_pCollider->SetOwner(this);
	}


	CMouse::~CMouse()
	{
		Release();
	}

	void CMouse::Initialize()
	{
		ZeroMemory(&m_tInfo, sizeof(m_tInfo));
		m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	}

	int CMouse::Update()
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);
		m_tInfo.vPos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
		
		D3DXMATRIX matScale, matRotateZ, matTranslate;
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matRotateZ);
		D3DXMatrixIdentity(&matTranslate);

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
		D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));
		D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

		m_tInfo.matWorld = matScale * matRotateZ * matTranslate;

		D3DXVec3TransformNormal(&m_tInfo.nvDir, &m_tInfo.nvLook, &m_tInfo.matWorld);
		D3DXVec3Normalize(&m_tInfo.nvDir, &m_tInfo.nvDir);

		return 0;
	}

	void CMouse::LateUpdate()
	{
	}

	void CMouse::Render()
	{
	}

	void CMouse::Release()
	{
		SafeDelete(m_pCollider);
	}



	void CMouse::Collision(CCollider * Collider)
	{
		cout << "Ãæµ¹!" << endl;
	}
	CCollider * CMouse::GetCollider()
	{
		return m_pCollider;
	}
	OBJID::ID CMouse::GetId()
	{
		return OBJID::MOUSE;
	}
}
