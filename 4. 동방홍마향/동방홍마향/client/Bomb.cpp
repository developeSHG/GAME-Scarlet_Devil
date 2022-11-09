#include "stdafx.h"
#include "Bomb.h"
#include "CircleCollider.h"

CBomb::CBomb()
	:m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_fSize = 1.f;
}


CBomb::~CBomb()
{
	SafeDelete(m_pCollider);
}

void CBomb::Initialize()
{
}

int CBomb::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	m_pCollider->SetColliderInfo(CircleInfo(m_fSize));
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
	++m_fSize;

	return OBJ_NOEVENT;
}

void CBomb::LateUpdate()
{
	if (m_fSize >= 300)
	{
		m_bIsDead = true;
	}
}

void CBomb::Render()
{
}

void CBomb::Release()
{
}

OBJID::ID CBomb::GetId()
{
	return OBJID::BOMB;
}

void CBomb::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::ENEMY_BULLET)
	{
		Collider->GetOwner()->Set_Dead();
	}
}

CCollider * CBomb::GetCollider()
{
	return m_pCollider;
}


