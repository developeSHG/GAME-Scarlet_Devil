#include "stdafx.h"
#include "SpreadBullet.h"


CSpreadBullet::CSpreadBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(6.f));
}


CSpreadBullet::~CSpreadBullet()
{
	SafeDelete(m_pCollider);
}

void CSpreadBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LStarBullet_b.png", L"LStarBullet_b");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LStarBullet_y.png", L"LStarBullet_y");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
}

int CSpreadBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate, matRotateZ;
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotateZ);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));

	m_tInfo.matWorld = matTranslate * matRotateZ * ParentWorldMat;

	m_tInfo.vPos -= D3DXVECTOR3(0.f, -2.f, 0.f);
	if (m_iBulletType == 1)
	{
		m_tInfo.fAngle = 276.f;
		m_tInfo.fAngle += 12.f*count;
	}
	else if (m_iBulletType == -1)
	{
		m_tInfo.fAngle = -282.f;
		m_tInfo.fAngle += -12.f*count;
	}



	return OBJ_NOEVENT;
}

void CSpreadBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CSpreadBullet::Render()
{
	if (m_iBulletType == 1)
	{
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"LStarBullet_b");
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
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"LStarBullet_y");
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

void CSpreadBullet::Release()
{
}


OBJID::ID CSpreadBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}
void CSpreadBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * CSpreadBullet::GetCollider()
{
	return m_pCollider;
}