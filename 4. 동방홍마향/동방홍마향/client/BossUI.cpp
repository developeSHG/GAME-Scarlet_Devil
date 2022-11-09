#include "stdafx.h"
#include "BossUI.h"
#include "HpOwner.h"

CBossUI::CBossUI()
{
}


CBossUI::~CBossUI()
{
}

void CBossUI::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvDir = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.vPos = D3DXVECTOR3(30.f, 30.f, 0.f);
}

int CBossUI::Update()
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
	return 0;
}

void CBossUI::LateUpdate()
{
	if (0 >= m_pHpOwner->GetCurrentHp())
		m_bIsDead = true;
}

void CBossUI::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Enemy_UI");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	m_tInfo.matWorld._41 += 80;
	const TEX_INFO* TextureInfo2 = CTextureMgr::GetInstance()->FindTexture(L"EnemyHp_UI");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	const float rate = m_pHpOwner->GetCurrentHp() / (float)m_pHpOwner->GetMaxHp();
	RECT rc;
	rc.top = 0;
	rc.left = 0;
	rc.right = TextureInfo2->tImgInfo.Width * rate;
	rc.bottom = TextureInfo2->tImgInfo.Height;
  	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo2->pTexture,
		&rc,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CBossUI::Release()
{
}

OBJID::ID CBossUI::GetId()
{
	return OBJID::UI;
}

void CBossUI::SetHpOwner(CHpOwner * _pHpOwner)
{
	m_pHpOwner = _pHpOwner;
}
