#include "stdafx.h"
#include "OddBullet.h"


COddBullet::COddBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(6.f));
}


COddBullet::~COddBullet()
{
	SafeDelete(m_pCollider);
}

void COddBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LStarBullet_b.png", L"LStarBullet_b");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LStarBullet_y.png", L"LStarBullet_y");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	dwTime = GetTickCount();
}

int COddBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate, matRotateZ;
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotateZ);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));

	m_tInfo.matWorld = matTranslate * matRotateZ * ParentWorldMat;

	m_tInfo.vPos -= D3DXVECTOR3(0.f, -1.f, 0.f);
	if (m_iBulletType == 1 && dwTime + 1000 > GetTickCount())
	{	
		m_tInfo.fAngle = 0.f;
		m_tInfo.fAngle += 22.5f*count;

	}
	else if (m_iBulletType == -1 && dwTime + 1000 > GetTickCount())
	{
		m_tInfo.fAngle = 0.f;
		m_tInfo.fAngle += 22.5f*count;
	}
	else if (m_iBulletType == 2 && dwTime + 1000 > GetTickCount())
	{
		m_tInfo.fAngle = 0.f;
		m_tInfo.fAngle += 22.5f*count;
	}

	if (dwTime + 1000 < GetTickCount() && m_iBulletType == 1)
	{
		m_tInfo.fAngle += 1.f;
		m_tInfo.vPos += D3DXVECTOR3(cosf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, -sinf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, 0.f);
	}
	else if (dwTime + 1000 < GetTickCount() && m_iBulletType == -1)
	{
		m_tInfo.fAngle -= 1.f;
		m_tInfo.vPos -= D3DXVECTOR3(cosf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, -sinf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, 0.f);
	}
	else if (dwTime + 1000 < GetTickCount() && m_iBulletType == 2)
	{
		m_tInfo.matWorld._42 -= 2.f;
	}
	return OBJ_NOEVENT;
}

void COddBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void COddBullet::Render()
{
	if (m_iBulletType == 1|| m_iBulletType == -1)
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
	else if (m_iBulletType == 2)
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

void COddBullet::Release()
{
}

OBJID::ID COddBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}
void COddBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * COddBullet::GetCollider()
{
	return m_pCollider;
}