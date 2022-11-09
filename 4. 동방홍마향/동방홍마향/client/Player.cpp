#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "KPlayerBullet.h"
#include "CircleCollider.h"
#include "Bomb.h"
#include "GuideBullet.h"
#include "PlayerShield.h"


//480 560
CPlayer::CPlayer()
	:m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(2.f));
}


CPlayer::~CPlayer()
{
	SafeDelete(m_pCollider);
}

void CPlayer::Initialize()
{
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/PlayerBullet.png", L"PlayerBullet");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/PlayerBullet1.png", L"PlayerBullet1");
	m_wsImageKey = L"Reimu";
	m_wsStateKey[STATE::HORIZON] = L"M_H";
	m_wsStateKey[STATE::VERTICAL] = L"M_V";
	m_eCurState = STATE::HORIZON;
	m_eNextState = STATE::HORIZON;

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Vertical/Reimu_M_V.png", m_wsImageKey, m_wsStateKey[STATE::VERTICAL], 4);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Horizon/Reimu_M_H.png", m_wsImageKey, m_wsStateKey[STATE::HORIZON], 6);

	CObjMgr::GetInstance()->AddObject(OBJID::SHIELD, CreateShield<CPlayerShield>(1));
	CObjMgr::GetInstance()->AddObject(OBJID::SHIELD, CreateShield<CPlayerShield>(2));

	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vPos = D3DXVECTOR3(260.f, 500.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();


	dwPlayerBullet = GetTickCount();
}

int CPlayer::Update()
{
	if (m_bIsDead == true)
		return OBJ_DEAD;

	m_eNextState = STATE::VERTICAL;
	KeyInput();
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

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	CheckFrame();
	UpdateFrame();
}

void CPlayer::Render()
{
	const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsStateKey[m_eCurState], m_tFrame.iFrameStart);
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsStateKey[m_eCurState], m_tFrame.iFrameStart)->pTexture,
		nullptr,
		&D3DXVECTOR3(test->tImgInfo.Width * 0.5f, test->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CPlayer::Release()
{
}



void CPlayer::KeyInput()
{

	if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.vPos += D3DXVECTOR3(-1.0f, 0.f, 0.f) * 3.f;
		m_tInfo.vSize.x = 1.f;
		m_eNextState = STATE::HORIZON;
	}
	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tInfo.vPos += D3DXVECTOR3(1.0f, 0.f, 0.f) * 3.f;
		m_tInfo.vSize.x = -1.f;
		m_eNextState = STATE::HORIZON;
	}
	if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
	{
		m_tInfo.vPos += D3DXVECTOR3(0.0f, -1.f, 0.f) * 3.f;
		m_eNextState = STATE::VERTICAL;
	}
	if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
	{
		m_tInfo.vPos += D3DXVECTOR3(0.0f, 1.f, 0.f) * 3.f;
		m_eNextState = STATE::VERTICAL;
	}
	if (CKeyMgr::GetInstance()->KeyPressing('B'))
	{
		CObjMgr::GetInstance()->AddObject(OBJID::BOMB, CAbstractFactory<CBomb>::CreateBullet(m_tInfo.vPos));
	}


	if (CKeyMgr::GetInstance()->KeyPressing(VK_SPACE) &&dwPlayerBullet + 50 < GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJID::PLAYER_BULLET, CreateBullet<CKPlayerBullet>(m_tInfo.vPos - D3DXVECTOR3(-7.0f, 0.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJID::PLAYER_BULLET, CreateBullet<CKPlayerBullet>(m_tInfo.vPos - D3DXVECTOR3(7.0f, 0.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJID::PLAYER_BULLET, CreateBullet<CGuideBullet>(m_tInfo.vPos - D3DXVECTOR3(-25.0f, 30.f, 0.f), 1));
		CObjMgr::GetInstance()->AddObject(OBJID::PLAYER_BULLET, CreateBullet<CGuideBullet>(m_tInfo.vPos - D3DXVECTOR3(25.0f, 30.f, 0.f), 2));
		dwPlayerBullet = GetTickCount();
	}

}

void CPlayer::CheckFrame()
{
	if (m_eCurState == m_eNextState)
		return;
	m_eCurState = m_eNextState;
	switch (m_eCurState)
	{
	case STATE::HORIZON:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 150;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::VERTICAL:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 150;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}

FRAME_STATE CPlayer::UpdateFrame()
{
	FRAME_STATE FrameState = NONE;

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
		FrameState = NEXT;
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;
		if (m_eCurState == STATE::HORIZON)
			m_tFrame.iFrameStart = 3;
		return FINISH;
	}

	return FrameState;
}

OBJID::ID CPlayer::GetId()
{
	return OBJID::PLAYER;
}

void CPlayer::Collision(CCollider * Collider)
{

}

CCollider * CPlayer::GetCollider()
{
	return m_pCollider;
}