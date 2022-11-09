#include "stdafx.h"
#include "FireworksBullet.h"


CFireworksBullet::CFireworksBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(6.f));
}

CFireworksBullet::~CFireworksBullet()
{
	SafeDelete(m_pCollider);
}

void CFireworksBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LBullet_g.png", L"LBullet_g");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LBullet_p.png", L"LBullet_p");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	dwTime = GetTickCount();
}

int CFireworksBullet::Update()
{
	if(m_bIsDead)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate, matRotateZ;
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotateZ);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));

	m_tInfo.matWorld = matTranslate * matRotateZ * ParentWorldMat;

	
	if(m_iBulletType == 1 && dwTime + 10 > GetTickCount())
	{
		m_tInfo.vPos -= D3DXVECTOR3(0.f, -2.f, 0.f);
		m_tInfo.fAngle = 0.f;
		m_tInfo.fAngle += 22.5f*count;

	}
	else if (m_iBulletType == -1 && dwTime + 10 > GetTickCount())
	{
		m_tInfo.vPos -= D3DXVECTOR3(0.f, -2.f, 0.f);
		m_tInfo.fAngle = 0.f;
		m_tInfo.fAngle += 22.5f*count;
	}
	
	if (dwTime + 10 < GetTickCount() && m_iBulletType == 1)
	{
		m_tInfo.vPos -= D3DXVECTOR3(2.f, -2.f, 0.f);
		m_tInfo.fAngle += 1.f;
		//m_tInfo.vPos -= D3DXVECTOR3(0.f, -2.5f, 0.f);
		m_tInfo.vPos += D3DXVECTOR3(cosf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, -sinf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, 0.f);
	}
	else if (dwTime + 10 < GetTickCount() && m_iBulletType == -1)
	{
		m_tInfo.vPos -= D3DXVECTOR3(-2.f, -2.f, 0.f);
		m_tInfo.fAngle += -1.f;
		//m_tInfo.vPos -= D3DXVECTOR3(0.f, -2.5f, 0.f);
		m_tInfo.vPos -= D3DXVECTOR3(cosf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, -sinf(m_tInfo.fAngle * 3.14 / 180.f)*5.f, 0.f);
	}
	
	//m_tInfo.fx = m_tPosin.x + cosf(m_fAngle * PI / 180.f) * m_fDist;
	//m_tInfo.fy = m_tPosin.y - sinf(m_fAngle * PI / 180.f) * m_fDist;

	return OBJ_NOEVENT;
}

void CFireworksBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CFireworksBullet::Render()
{
	if (m_iBulletType == 1)
	{
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"LBullet_g");
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
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"LBullet_p");
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

void CFireworksBullet::Release()
{
}

OBJID::ID CFireworksBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}

void CFireworksBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * CFireworksBullet::GetCollider()
{
	return m_pCollider;
}

