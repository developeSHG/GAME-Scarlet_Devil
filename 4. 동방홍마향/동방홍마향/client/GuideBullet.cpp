#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "CircleCollider.h"

CGuideBullet::CGuideBullet()
	:m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(20.f));
}


CGuideBullet::~CGuideBullet()
{
	SafeDelete(m_pCollider);
}

void CGuideBullet::Initialize()
{
	CTextureMgr::GetInstance()->FindTexture(L"../Texture/Bullet/PlayerBullet1.png", L"PlayerBullet1");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_pMonster = CObjMgr::GetInstance()->Get_Monster();

	if (m_pMonster != nullptr)
	{
		fMonsterX = m_pMonster->Get_Info().vPos.x;
		m_pPlayer = CObjMgr::GetInstance()->Get_Player();
	}
	else
		m_bIsDead = true;

}

int CGuideBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	D3DXMATRIX matTranslate;
	D3DXMatrixIdentity(&matTranslate);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = matTranslate;
	D3DXVec3TransformNormal(&m_tInfo.nvDir, &m_tInfo.nvLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.nvDir, &m_tInfo.nvDir);
	m_tInfo.vPos -= D3DXVECTOR3(0.f, 5.f, 0.f);
	float Dist = fMonsterX - m_tInfo.vPos.x;
	if (m_tInfo.vPos.x >= fMonsterX)
		m_tInfo.vPos.x += Dist / 15;
	else if(m_tInfo.vPos.x <= fMonsterX)
		m_tInfo.vPos.x += Dist / 15;
	//m_tInfo.vPos -= D3DXVECTOR3(m_pMonster->Get_Info().nvDir.x, m_pMonster->Get_Info().nvDir.y, 0.f);
	return OBJ_NOEVENT;
}

void CGuideBullet::LateUpdate()
{
	if (m_tInfo.matWorld._41 < 30 || m_tInfo.matWorld._41>485 ||
		m_tInfo.matWorld._42 < 30 || m_tInfo.matWorld._42>570)
		m_bIsDead = true;
}

void CGuideBullet::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"PlayerBullet1");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

}

void CGuideBullet::Release()
{
}

OBJID::ID CGuideBullet::GetId()
{
	//return OBJID::BULLET;
	return OBJID::PLAYER_BULLET;
}

void CGuideBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::ENEMY)
		m_bIsDead = true;
}

CCollider * CGuideBullet::GetCollider()
{
	return m_pCollider;
}
