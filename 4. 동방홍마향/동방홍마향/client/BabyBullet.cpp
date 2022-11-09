#include "stdafx.h"
#include "BabyBullet.h"
#include "ObjMgr.h"


CBabyBullet::CBabyBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(6.f));
}


CBabyBullet::~CBabyBullet()
{
	SafeDelete(m_pCollider);
}

void CBabyBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LStarBullet_b.png", L"LStarBullet_b");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/BulletL/LStarBullet_y.png", L"LStarBullet_y");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	dwTime = GetTickCount();
}

int CBabyBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	m_pPlayer = CObjMgr::GetInstance()->Get_Player();

	D3DXMATRIX matTranslate, matRotateZ;
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotateZ);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));
	//m_pPlayer->Get_Info().nvDir
	//m_tInfo.vPos += m_pPlayer->Get_Info().nvDir;
	m_tInfo.vPos += D3DXVECTOR3(0.f, 3.f, 0.f);
	m_tInfo.matWorld = matTranslate * matRotateZ * ParentWorldMat;

	

	if (m_iBulletType == 1)
	{
		m_tInfo.fAngle = 30.f;
		m_tInfo.fAngle += 25.f*count;
	}
	else if (m_iBulletType == 2)
	{
		m_tInfo.fAngle = 30.f;
		m_tInfo.fAngle += 25.f*count;
	}
	else if (m_iBulletType == 3)
	{
		m_tInfo.fAngle = 30.f;
		m_tInfo.fAngle += 25.f*count;
	}

	return OBJ_NOEVENT;
}

void CBabyBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CBabyBullet::Render()
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
	else if(m_iBulletType == 2)
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

void CBabyBullet::Release()
{
}

OBJID::ID CBabyBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}

void CBabyBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * CBabyBullet::GetCollider()
{
	return m_pCollider;
}
