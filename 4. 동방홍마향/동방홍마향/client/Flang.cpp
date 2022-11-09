#include "stdafx.h"
#include "Flang.h"
#include "CircleCollider.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "EBullet.h"
#include "BossUI.h"
CFlang::CFlang()
	:m_pCollider(nullptr)
{
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(20.f));
}


CFlang::~CFlang()
{
	SafeDelete(m_pCollider);
}

void CFlang::Initialize()
{
	m_eCurState = STATE::STAND;
	MoveLR = 0;

	m_wsImageKey = L"Flang";
	m_wsStateKey[STATE::MOVELEFT] = L"MOVELEFT";
	m_wsStateKey[STATE::MOVERIGHT] = L"MOVERIGHT";
	m_wsStateKey[STATE::STAND] = L"STAND";
	m_wsStateKey[STATE::BACK] = L"MAGICAL";

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/FlangBack2.png", m_wsStateKey[STATE::BACK]);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/FlangMoveLeft.png", m_wsStateKey[STATE::MOVELEFT]);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/FlangMoveRight.png", m_wsStateKey[STATE::MOVERIGHT]);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/FlangStand.png", m_wsImageKey, m_wsStateKey[STATE::STAND], 4);

	ZeroMemory(&m_tInfo, sizeof(m_tInfo));

	m_tInfo.vPos = D3DXVECTOR3(260.f, 100.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.nvDir = D3DXVECTOR3(1.f, 1.f, 0.f);

	m_d3dxCenter = m_tInfo.vPos;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
	magicangle = 1.f;

	Level1 = 100;
	Level2 = 100;
	Level3 = 100;
	m_bInvincibletime = false;
	CBossUI* BossUI = new CBossUI;
	BossUI->Initialize();
	BossUI->SetHpOwner(this);
	CObjMgr::GetInstance()->AddObject(BossUI->GetId(), BossUI);
	 Switch1 = false;
	 Switch2=false;

}

int CFlang::Update()
{

	if (Level1 == 0 && Level2 == 0 && Level3 == 0)
		return OBJ_DEAD;

	D3DXVECTOR3 TEMP = m_tInfo.vPos;

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

	--magicangle;

	D3DXMATRIX matRotateZtemp;
	D3DXMatrixIdentity(&matRotateZtemp);
	D3DXMatrixRotationZ(&matRotateZtemp, magicangle);
	TEMPM = matScale *matRotateZtemp* matTranslate;

	if (Level1 > 0 && m_bInvincibletime == false)
	{
		BulletPatern(PATERN::SPREAD);
	}
	if (Level1 <= 0 && Switch1==false)
	{
		m_bInvincibletime = true;
		MoveCENTER();
	}
	if (Level1 <= 0 && Level2 > 0 && m_bInvincibletime == false)
	{
		Level1 = 0;
		BulletPatern(PATERN::GATLING);
	}
	if (Level1 <= 0 && Level2 <= 0 && Switch2 == false)
	{
		m_bInvincibletime = true;
		MoveCENTER();
	}
	if (Level2 <= 0 && m_bInvincibletime == false)
	{
		Level2 = 0;
		BulletPatern(PATERN::BOUNCE);
	}

	
	

	return OBJ_NOEVENT;
}

void CFlang::LateUpdate()
{
	CheckFrame();
	UpdateFrame();
	
}

void CFlang::Render()
{

	if (m_eCurState == STAND)
	{
		const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsStateKey[m_eCurState], m_tFrame.iFrameStart);
		CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDeviceMgr::GetInstance()->GetSprite()->Draw(
			test->pTexture,
			0,
			&D3DXVECTOR3(test->tImgInfo.Width / 2.f, test->tImgInfo.Height / 2.f, 0.0f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	else
	{
		const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsStateKey[m_eCurState]);
		CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDeviceMgr::GetInstance()->GetSprite()->Draw(
			test->pTexture,
			0,
			&D3DXVECTOR3(test->tImgInfo.Width / 2.f, test->tImgInfo.Height / 2.f, 0.0f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}

	const TEX_INFO* test2 = CTextureMgr::GetInstance()->FindTexture(L"MAGICAL");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&TEMPM);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		test2->pTexture,
		0,
		&D3DXVECTOR3(test2->tImgInfo.Width * 0.5f, test2->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(100, 255, 255, 255)
	);
}

void CFlang::Release()
{
}

void CFlang::MoveCENTER()
{
	if (m_tInfo.vPos.x < m_d3dxCenter.x)
	{
		++m_tInfo.vPos.x;
		m_eNextState = MOVERIGHT;
	}
	if (m_tInfo.vPos.x > m_d3dxCenter.x)
	{
		--m_tInfo.vPos.x;
		m_eNextState = MOVELEFT;
	}
	if (fabs(m_tInfo.vPos.x - m_d3dxCenter.x)<=2.f && fabs(m_tInfo.vPos.x - m_d3dxCenter.x) >= 0)
	{
		m_bInvincibletime = false;
		if(Level1<=0 &&Level2<=0)
		Switch2 = true;
		else if(Level1 <= 0)
			Switch1 = true;

		return;
	}
}

void CFlang::CheckFrame()
{

	if (m_eCurState == m_eNextState)
		return;
	else
	{
		switch (m_eNextState)
		{
		case CFlang::STAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			m_eCurState = m_eNextState;
			break;
		case CFlang::MOVELEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_eCurState = m_eNextState;
			break;
		case CFlang::MOVERIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_eCurState = m_eNextState;
			break;
		case CFlang::MOVECENTER:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_eCurState = m_eNextState;
		case CFlang::STATE_END:
			break;
		default:
			break;
		}
	}
}

void CFlang::UpdateFrame()
{

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
		}
	}
}

void CFlang::BulletPatern(PATERN pID)
{
	PATERNID = pID;

	switch (PATERNID)
	{
	case PATERN::SPREAD:
	{
		++MoveLR;
		if (MoveLR > 500)
		{
			MoveLR = 100;
		}
		else if (MoveLR > 300)
		{
			m_eNextState = MOVERIGHT;
			m_tInfo.vPos -= D3DXVECTOR3(-1.0f, 0.f, 0.f) * 1.f;
			if (MoveLR == 330 || MoveLR == 360 || MoveLR == 390 || MoveLR == 420 || MoveLR == 450 || MoveLR == 480)
			{
				for (int i = 0; i <= 71; ++i)
				{
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::SPREAD, BULLET::REDSMALL, m_tInfo.vPos, i*5.f));
				}
			}
		}
		else if (MoveLR > 100)
		{
			m_eNextState = MOVELEFT;
			m_tInfo.vPos += D3DXVECTOR3(-1.0f, 0.f, 0.f) * 1.f;
			if (MoveLR == 120 || MoveLR == 150 || MoveLR == 180 || MoveLR == 210 || MoveLR == 240 || MoveLR == 270)
			{
				for (int i = 0; i <= 71; ++i)
				{
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::SPREAD, BULLET::REDSMALL, m_tInfo.vPos, i*5.f));
				}
			}
		}
		else if (MoveLR > 0)
		{
			m_eNextState = MOVERIGHT;
			m_tInfo.vPos -= D3DXVECTOR3(-1.0f, 0.f, 0.f) * 1.f;
			if (MoveLR == 30 || MoveLR == 60 || MoveLR == 90)
			{
				for (int i = 0; i <= 71; ++i)
				{
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::SPREAD, BULLET::REDSMALL, m_tInfo.vPos, i*5.f));
				}
			}
		}
	}break;
	case PATERN::BOUNCE:
	{
		m_eNextState = STAND;
		D3DXVECTOR3 TEMPL = { m_tInfo.vPos.x - 100,m_tInfo.vPos.y + 50 ,0 };
		D3DXVECTOR3 TEMPR = { m_tInfo.vPos.x + 100,m_tInfo.vPos.y + 50 ,0 };
		D3DXVECTOR3 TEMPD = { m_tInfo.vPos.x ,m_tInfo.vPos.y + 150 ,0 };
		D3DXVECTOR3 TEMPU = { m_tInfo.vPos.x ,m_tInfo.vPos.y - 50 ,0 };
		++MoveLR;
		if ((MoveLR % 211) == 0)
		{
			int random = rand() % 4;

			for (int i = 0; i <= 71; ++i)
			{
				float tempAngle = i*5.f;
				if (random == 0)
				{
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::BOUNCE, BULLET::REDSNOW, TEMPL, tempAngle));
				}
				else if (random == 1)
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::BOUNCE, BULLET::REDSNOW, TEMPR, tempAngle));
				else if (random == 2)
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::BOUNCE, BULLET::REDSNOW, TEMPD, tempAngle));
				else if (random == 3)
					CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
						CAbstractFactory<CEBullet>::CreateEBullet(PATERN::BOUNCE, BULLET::REDSNOW, TEMPU, tempAngle));
			}
		}
	}break;
	case PATERN::GATLING:
	{
		++MoveLR;
		if (MoveLR >= 350)
		{
			MoveLR = 150;
		}
		else if (MoveLR >= 250)
		{
			m_eNextState = MOVERIGHT;
			m_tInfo.vPos -= D3DXVECTOR3(-1.0f, 0.f, 0.f) * 2.f;
		}
		else if (MoveLR >= 150)
		{
			m_eNextState = MOVELEFT;
			m_tInfo.vPos += D3DXVECTOR3(-1.0f, 0.f, 0.f) * 2.f;
		}
		else if (MoveLR >= 50)
		{
			m_eNextState = MOVERIGHT;
			m_tInfo.vPos -= D3DXVECTOR3(-1.0f, 0.f, 0.f) * 2.f;
		}
		else if (MoveLR > 0)
			m_eNextState = STAND;

		if (dwPlayerBullet + 150 < GetTickCount())
		{
			float randomangle = rand() % 120 + 210;
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
				CAbstractFactory<CEBullet>::CreateEBullet(PATERN::GATLING, BULLET::REDBIG, m_tInfo.vPos, randomangle));

			dwPlayerBullet = GetTickCount();

		}

	}break;
	default:
		break;
	}
}

int CFlang::GetCurrentHp() const
{

	return Level1+Level2+Level3;
}

int CFlang::GetMaxHp() const
{
	return 300;
}

OBJID::ID CFlang::GetId()
{
	return OBJID::ENEMY;
}

void CFlang::Collision(CCollider * Collider)
{
	if (OBJID::PLAYER_BULLET == Collider->GetOwner()->GetId())
	{
		//보스체력감소
		Set_Level();
	}
}

CCollider * CFlang::GetCollider()
{
	return m_pCollider;
}


