#include "stdafx.h"
#include "ParentBullet.h"
#include "BabyBullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"


CParentBullet::CParentBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(12.f));
}


CParentBullet::~CParentBullet()
{
	SafeDelete(m_pCollider);
}

void CParentBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/Bullet/Bullet_B.png", L"Bullet_B");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/Bullet/Bullet_Y.png", L"Bullet_Y");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	dwTime = GetTickCount();
}

int CParentBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate, matRotateZ;
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotateZ);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));

	m_tInfo.matWorld = matTranslate * matRotateZ * ParentWorldMat;

	m_tInfo.vPos -= D3DXVECTOR3(0.f, -4.f, 0.f);
	if (m_iBulletType == 3)
	{
		static bool ck = false;
		static int count = 1;
		if (ParentWorldMat._41 > 300)
		{
			m_tInfo.fAngle = 85.f;
			m_tInfo.fAngle += 5.f;
		}
		else
		{
			m_tInfo.fAngle = -85.f;
			m_tInfo.fAngle += -5.f;
		}
		//dwTime = GetTickCount();
		if (dwTime + 80 < GetTickCount())
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CBabyBullet>(m_tInfo.matWorld, count, 1));
			dwTime = GetTickCount();
			count++;
		}
		if (m_bIsDead)
			count = 0;
	}
	else if (m_iBulletType == 1)
	{
		static bool ck = false;
		static int count = 1;
		m_tInfo.fAngle = 355.f;
		m_tInfo.fAngle += 5.f;
		//dwTime = GetTickCount();
		if (dwTime + 80 < GetTickCount())
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CBabyBullet>(m_tInfo.matWorld, count, 1));
			dwTime = GetTickCount();
			count++;
		}
		if (m_bIsDead)
			count = 0;
	}
	else if (m_iBulletType == 2)
	{
		static bool ck = false;
		static int count = 1;
		if (ParentWorldMat._41 > 300)
		{
			m_tInfo.fAngle = 40.f;
			m_tInfo.fAngle += 5.f;
		}
		else
		{
			m_tInfo.fAngle = -40.f;
			m_tInfo.fAngle += -5.f;
		}
		
		//dwTime = GetTickCount();
		if (dwTime + 80 < GetTickCount())
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CBabyBullet>(m_tInfo.matWorld, count, 2));
			dwTime = GetTickCount();
			count++;
		}
		if (m_bIsDead)
			count = 0;
	}

	return OBJ_NOEVENT;
}

void CParentBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CParentBullet::Render()
{
	if (m_iBulletType == 1 || m_iBulletType == 3)
	{
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Bullet_B");
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
		const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Bullet_Y");
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

void CParentBullet::Release()
{
}

OBJID::ID CParentBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}

void CParentBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * CParentBullet::GetCollider()
{
	return m_pCollider;
}
