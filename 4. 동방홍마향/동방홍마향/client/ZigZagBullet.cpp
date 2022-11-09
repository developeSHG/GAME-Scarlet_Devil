#include "stdafx.h"
#include "ZigZagBullet.h"



CZigZagBullet::CZigZagBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(6.f));
}


CZigZagBullet::~CZigZagBullet()
{
	SafeDelete(m_pCollider);
}

void CZigZagBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/Lzigzag_b.png", L"Lzigzag_b");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/Lzigzag_m.png", L"Lzigzag_m");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	
}

int CZigZagBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate, matRotateZ;
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotateZ);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));
	
	m_tInfo.matWorld = matTranslate * matRotateZ * ParentWorldMat;
	m_tInfo.vPos -= D3DXVECTOR3(0.f, -5.f, 0.f);
	
	if (m_iBulletType == 1)
	{
		m_tInfo.fAngle = 280.f;
		m_tInfo.fAngle += 10.f*count;
	}
	else if (m_iBulletType == -1)
	{
		m_tInfo.fAngle = -280.f;
		m_tInfo.fAngle += -10.f*count;
	}

	return OBJ_NOEVENT;
}

void CZigZagBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CZigZagBullet::Render()
{
	if (m_iBulletType == 1)
	{
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Lzigzag_b");
		CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDeviceMgr::GetInstance()->GetSprite()->Draw(
			TextureInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	else if (m_iBulletType == -1)
	{
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Lzigzag_m");
		CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDeviceMgr::GetInstance()->GetSprite()->Draw(
			TextureInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

void CZigZagBullet::Release()
{
}


OBJID::ID CZigZagBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}

void CZigZagBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * CZigZagBullet::GetCollider()
{
	return m_pCollider;
}
