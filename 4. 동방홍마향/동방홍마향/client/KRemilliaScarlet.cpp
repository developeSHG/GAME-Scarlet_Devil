#include "stdafx.h"
#include "KRemilliaScarlet.h"
#include "RectCollider.h"
#include "BossUI.h"
#include "ObjMgr.h"
CKRemilliaScarlet::CKRemilliaScarlet()
	: m_pCollider(nullptr), Pattern(this), m_iHealth(60), m_iMaxHealth(60)
{
	m_pCollider = new CRectCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(RectInfo(42.f, 77.f));
}


CKRemilliaScarlet::~CKRemilliaScarlet()
{
	Release();
}

void CKRemilliaScarlet::Initialize()
{
	m_wsImageKey = L"RemilliaScarlet";
	m_wsStateKey[STATE::STAND] = L"S";
	m_wsStateKey[STATE::MOVE] = L"M_H";
	m_eCurState = STATE::STAND;
	m_eNextState = STATE::STAND;

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Stand/RemilliaScarlet_S.png", m_wsImageKey, m_wsStateKey[STATE::STAND], 1);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Horizon/RemilliaScarlet_M_H.png", m_wsImageKey, m_wsStateKey[STATE::MOVE], 2);

	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vPos = D3DXVECTOR3(260.f, 200.f, 0.f);

	//m_tInfo.vPos = D3DXVECTOR3(260.f, 100.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, 1.f, 0.f);

	Pattern.Initialize();

	//HPBar
	CBossUI* BossUI = new CBossUI;
	BossUI->Initialize();
	BossUI->SetHpOwner(this);
	CObjMgr::GetInstance()->AddObject(BossUI->GetId(), BossUI);
}

int CKRemilliaScarlet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

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

	Pattern.Update();

	return OBJ_NOEVENT;
}

void CKRemilliaScarlet::LateUpdate()
{
	CheckFrame();
	UpdateFrame();

	Pattern.LateUpdate();
}

void CKRemilliaScarlet::Render()
{
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsStateKey[m_eCurState], m_tFrame.iFrameStart);

	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsStateKey[m_eCurState], m_tFrame.iFrameStart)->pTexture,
		nullptr,
		&D3DXVECTOR3(test->tImgInfo.Width * 0.5f, test->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CKRemilliaScarlet::Release()
{
	SafeDelete(m_pCollider);
	CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY_BULLET);
}

void CKRemilliaScarlet::CheckFrame()
{
	if (m_eCurState == m_eNextState)
		return;
	m_eCurState = m_eNextState;
	switch (m_eCurState)
	{
	case STATE::STAND:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 150;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::MOVE:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 2;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 150;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}

FRAME_STATE CKRemilliaScarlet::UpdateFrame()
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
		if (m_eCurState == STATE::MOVE)
			m_tFrame.iFrameStart = 1;
		return FINISH;
	}

	return FrameState;
}

int CKRemilliaScarlet::GetCurrentHp() const
{
	return m_iHealth;
}

int CKRemilliaScarlet::GetMaxHp() const
{
	return m_iMaxHealth;
}

OBJID::ID CKRemilliaScarlet::GetId()
{
	return OBJID::ENEMY;
}

void CKRemilliaScarlet::Collision(CCollider * Collider)
{
	if (OBJID::PLAYER_BULLET == Collider->GetOwner()->GetId())
	{
		Collider->GetOwner()->Set_Dead();
		--m_iHealth;
		if(0 >= m_iHealth)
			m_bIsDead = true;
	}
}

CCollider * CKRemilliaScarlet::GetCollider()
{
	return m_pCollider;
}
