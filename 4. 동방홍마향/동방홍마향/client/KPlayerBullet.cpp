#include "stdafx.h"
#include "KPlayerBullet.h"
#include "CircleCollider.h"
#include "Flang.h"

CKPlayerBullet::CKPlayerBullet()
{
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(6.f));
}


CKPlayerBullet::~CKPlayerBullet()
{
	SafeDelete(m_pCollider);
}

OBJID::ID CKPlayerBullet::GetId()
{
	return OBJID::PLAYER_BULLET;
}

void CKPlayerBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::ENEMY)
	{
		m_bIsDead = true;
		/*dynamic_cast<CFlang*>(Collider->GetOwner())->Set_Level();*/
	}
}

CCollider * CKPlayerBullet::GetCollider()
{
	return m_pCollider;
}

void CKPlayerBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/Bullet/PlayerBullet.png", L"PlayerBullet");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.nvDir = D3DXVECTOR3(1.f, 1.f, 0.f);
}

int CKPlayerBullet::Update()
{
	if (m_bIsDead == true)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate;
	D3DXMatrixIdentity(&matTranslate);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = matTranslate;

	m_tInfo.vPos -= D3DXVECTOR3(0.f, 5.f, 0.f);

	return OBJ_NOEVENT;
}

void CKPlayerBullet::LateUpdate()
{
	if (m_tInfo.vPos.x < 20 || m_tInfo.vPos.x>480 || m_tInfo.vPos.y < 20 || m_tInfo.vPos.y > 580)
		m_bIsDead = true;
}

void CKPlayerBullet::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"PlayerBullet");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CKPlayerBullet::Release()
{
}
