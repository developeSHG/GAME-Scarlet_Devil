#include "stdafx.h"
#include "PlayerShield.h"
#include "ObjMgr.h"

CPlayerShield::CPlayerShield()
{
}


CPlayerShield::~CPlayerShield()
{
}

void CPlayerShield::Initialize()
{
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Shield/PlayerShield.png", L"PlayerShield");
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	//m_tInfo.vPos = D3DXVECTOR3(260.f, 500.f, 0.f);
	
}

int CPlayerShield::Update()
{
	m_pPlayer = CObjMgr::GetInstance()->Get_Player();


	if(m_iBulletType == 1)
		m_tInfo.vPos = D3DXVECTOR3(25.f, 0.f, 0.f);
	else if(m_iBulletType == 2)
		m_tInfo.vPos = D3DXVECTOR3(-25.f, 0.f, 0.f);

	D3DXMATRIX matTranslate, matRotateZ, pmatScale, pmatRotateZ, pmatTranslate;
	D3DXMatrixIdentity(&matRotateZ);
	D3DXMatrixIdentity(&matTranslate);
	
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));
	D3DXMatrixTranslation(&matTranslate, -m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

//	D3DXMatrixIdentity(&pmatScale);
//	D3DXMatrixIdentity(&pmatRotateZ);
//	D3DXMatrixIdentity(&pmatTranslate);
//	
//	D3DXMatrixScaling(&pmatScale, m_pPlayer->Get_Info().vSize.x, m_pPlayer->Get_Info().vSize.y, m_pPlayer->Get_Info().vSize.z);
//	D3DXMatrixRotationZ(&pmatRotateZ, D3DXToRadian(m_pPlayer->Get_Info().fAngle));
//	D3DXMatrixTranslation(&pmatTranslate, m_pPlayer->Get_Info().vPos.x, m_pPlayer->Get_Info().vPos.y, m_pPlayer->Get_Info().vPos.z);
//
//	m_pPlayer->Get_Info().matWorld = pmatScale * pmatRotateZ * pmatTranslate;



	m_tInfo.matWorld = matTranslate * matRotateZ * m_pPlayer->Get_Info().matWorld;


	return OBJ_NOEVENT;
}

void CPlayerShield::LateUpdate()
{
}

void CPlayerShield::Render()
{

	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"PlayerShield");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CPlayerShield::Release()
{
}

OBJID::ID CPlayerShield::GetId()
{
	return OBJID::SHIELD;
}
