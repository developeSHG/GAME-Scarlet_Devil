#include "stdafx.h"
#include "BasicBullet.h"


CBasicBullet::CBasicBullet()
	: m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(12.f));
}


CBasicBullet::~CBasicBullet()
{
	SafeDelete(m_pCollider);
}

void CBasicBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/Bullet/Bullet_B.png", L"Bullet_B");
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/Bullet/Bullet_Y.png", L"Bullet_Y");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	dwTime = GetTickCount();
}

int CBasicBullet::Update()
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

	return OBJ_NOEVENT;
}

void CBasicBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CBasicBullet::Render()
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

void CBasicBullet::Release()
{
}

OBJID::ID CBasicBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}

void CBasicBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
	}
}

CCollider * CBasicBullet::GetCollider()
{
	return m_pCollider;
}
