#include "stdafx.h"
#include "LMonster.h"
#include "ZigZagBullet.h"
#include "SpreadBullet.h"
#include "FlowerBullet.h"
#include "ParentBullet.h"
#include "BasicBullet.h"
#include "FireworksBullet.h"
#include "OddBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossUI.h"

CLMonster::CLMonster()
	: m_pCollider(nullptr), m_iHp(100), m_iMaxHp(100)
{
	m_pCollider = new CCircleCollider();
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(16.f));
}


CLMonster::~CLMonster()
{
	SafeDelete(m_pCollider);
}

void CLMonster::Initialize()
{
	m_wsImageKey = L"Rumia";
	m_wsStateKey[STATE::HORIZON] = L"M_H";
	m_wsStateKey[STATE::VERTICAL] = L"M_V";
	m_eCurState = STATE::HORIZON;
	m_eNextState = STATE::HORIZON;
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/Bullet_B.png", L"Bullet_B");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/Bullet_Y.png", L"Bullet_Y");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/LStarBullet_b.png", L"LStarBullet_b");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/LStarBullet_y.png", L"LStarBullet_y");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/LBullet_g.png", L"LBullet_g");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/LBullet_p.png", L"LBullet_p");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/Lzigzag_b.png", L"Lzigzag_b");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/BulletL/Lzigzag_m.png", L"Lzigzag_m");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Vertical/Rumia_M_V.png", m_wsImageKey, m_wsStateKey[STATE::VERTICAL], 5);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Horizon/Rumia_M_H.png", m_wsImageKey, m_wsStateKey[STATE::HORIZON], 4);

	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vPos = D3DXVECTOR3(260.f, 100.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, 1.f, 0.f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fSpeed = 3.f;
	dwMonsterBullet = GetTickCount();
	dwMonsterMove = GetTickCount();
	dwTime = GetTickCount();
	dwBasicTime = GetTickCount();

	Move = false;
	Att = true;
	MoveCount = 1;
	MonsterDir = 1;

	//HpBar
	CBossUI* BossUI = new CBossUI;
	BossUI->Initialize();
	BossUI->SetHpOwner(this);
	CObjMgr::GetInstance()->AddObject(BossUI->GetId(), BossUI);
}

int CLMonster::Update()
{
	if (m_bIsDead == true)
		return OBJ_DEAD;

	//m_eNextState = STATE::VERTICAL;

	D3DXMATRIX matScale, matRotateZ, matTranslate;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotateZ);
	D3DXMatrixIdentity(&matTranslate);

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
	D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));
	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	//m_tInfo.vPos += D3DXVECTOR3(m_fSpeed, 0.f, 0.f);
	m_tInfo.matWorld = matScale * matRotateZ * matTranslate;

	D3DXVec3TransformNormal(&m_tInfo.nvDir, &m_tInfo.nvLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.nvDir, &m_tInfo.nvDir);

	
	//ZigZagPattern();
	//SpreadParentPattern();
	//FlowerPattern();
	//FireworksOddPattern();


	if (m_iHp > 75)
		ZigZagPattern();
	else if (m_iHp <= 75 && m_iHp > 50)
		FlowerPattern();
	else if (m_iHp <= 50 && m_iHp > 25)
		SpreadParentPattern();
	else if (m_iHp <= 25)
		FireworksOddPattern();

	//ZigZagBullet();
	//SpreadBullet();
	//FlowerBullet();
	//ParentBullet();
	//FireworksBullet();
	//OddBullet();
	
	
	return OBJ_NOEVENT;
}

void CLMonster::LateUpdate()
{
	CheckFrame();
	//if (20 > m_tInfo.vPos.x || WINCX - 300 < m_tInfo.vPos.x)
	//	m_fSpeed *= -1.f;
	if (m_fSpeed > 0)
	{
		m_eNextState = STATE::HORIZON;
		m_tInfo.vSize.x = 1.f;
	}
	else if (m_fSpeed < 0)
	{
		m_eNextState = STATE::HORIZON;
		m_tInfo.vSize.x = -1.f;
	}


	UpdateFrame();
}

void CLMonster::Render()
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

void CLMonster::Release()
{
}

void CLMonster::CheckFrame()
{
	if (m_eCurState == m_eNextState)
		return;
	m_eCurState = m_eNextState;
	switch (m_eCurState)
	{
	case STATE::HORIZON:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 150;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::VERTICAL:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 150;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}

FRAME_STATE CLMonster::UpdateFrame()
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

int CLMonster::ZigZagBullet()
{
	static int count = 0;
	static int count1 = 0;
	static int type = 1;
	static bool ck = false;
	if (count1 >= 4)
	{
		count1 = 0;
		ck = false;
	}
	if (dwMonsterBullet + 30 < GetTickCount() && ck == false)
	{
		++count;
		if (type == 1)
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CZigZagBullet>(m_tInfo.matWorld, count, 1));
		else if (type == -1)
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CZigZagBullet>(m_tInfo.matWorld, count, -1));
		dwMonsterBullet = GetTickCount();
		if (count > 10)
		{
			count = 0;
			count1++;
			type *= -1;
			dwTime = GetTickCount();
		}
	}
	if (count1 >= 4)
	{
		ck = true;
	} 
	return count1;
}

int CLMonster::SpreadBullet()
{
	static bool ck = false;
	static int type = 1;
	static int count = 0;
	if (count >= 4)
	{
		count = 0;
		ck = false;
	}
	if (dwMonsterBullet + 300 < GetTickCount() && ck == false)
	{
		if (type == 1)
		{
			for (int i = 0; i < 15; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CSpreadBullet>(m_tInfo.matWorld, i, 1));
			}
			dwTime = GetTickCount();
			type = -1;
		}
		if (dwTime + 300 < GetTickCount() && type == -1)
		{
			for (int i = 0; i < 14; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CSpreadBullet>(m_tInfo.matWorld, i, -1));
			}
			//ck = true;
			count++;
			dwMonsterBullet = GetTickCount();
			dwTime = GetTickCount();
			type = 1;
		}
		
	}
	if (count >= 4)
	{
		ck = true;
		
	}
	return count;
}

int CLMonster::FlowerBullet()
{
	static bool ck = false;
	static int type = 1;
	static int count = 0;
	if (count >= 4)
	{
		count = 0;
		ck = false;
	}
	if (dwMonsterBullet + 300 < GetTickCount() && ck == false)
	{
		if (type == 1)
		{
			for (int i = 0; i < 8; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFlowerBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 8; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFlowerBullet>(m_tInfo.matWorld, i, -1));
			}
			
			dwTime = GetTickCount();
			type = -1;
		}
		if (dwTime + 300 < GetTickCount() && type == -1)
		{
			for (int i = 0; i < 8; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFlowerBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 8; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFlowerBullet>(m_tInfo.matWorld, i, -1));
			}
			type = 2;
			dwTime = GetTickCount();
		}
		if (dwTime + 300 < GetTickCount() && type == 2)
		{
			for (int i = 0; i < 8; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFlowerBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 8; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFlowerBullet>(m_tInfo.matWorld, i, -1));
			}
			ck = true;
			dwTime = GetTickCount();
		}
	
	}

	if (dwTime + 1000 < GetTickCount())
	{
		ck = false;
		type = 1;
		count++;
	}
	if (count >= 4)
	{
		ck = true;
	}
	
	return count;
}

int CLMonster::ParentBullet()
{
	static bool ck = false;
	static int type = 1;
	static int count = 0;
	if (count >= 4)
	{
		count = 0;
		ck = false;
	}
	if (dwMonsterBullet + 300 < GetTickCount() && ck == false)
	{
		if (type == 1)
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CParentBullet>(m_tInfo.matWorld, 1, 1));
			type = 2;
			dwTime = GetTickCount();
		}
		if (dwTime + 300 < GetTickCount() && type == 2)
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CParentBullet>(m_tInfo.matWorld, 1, 2));
			type = 3;
			dwTime = GetTickCount();
		}
		if (dwTime + 300 < GetTickCount() && type == 3)
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CParentBullet>(m_tInfo.matWorld, 1, 3));
			dwTime = GetTickCount();
			ck = true;
		}
	}
	
	if (dwTime + 1500 < GetTickCount())
	{
		ck = false;
		type = 1;
		count++;
	}
	if (count >= 4)
	{
		ck = true;

	}
	return count;
}

int CLMonster::FireworksBullet()
{
	static bool ck = false;
	static int type = 1;
	static int count = 0;
	if (count >= 4)
	{
		count = 0;
		ck = false;
	}
	if (dwMonsterBullet + 300 < GetTickCount() && ck == false)
	{
		if (type == 1)
		{
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFireworksBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFireworksBullet>(m_tInfo.matWorld, i, -1));
			}
			
			
			dwTime = GetTickCount();
			type = -1;
		}
		if (dwTime + 300 < GetTickCount() && type == -1)
		{
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFireworksBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFireworksBullet>(m_tInfo.matWorld, i, -1));
			}
			
			type = 2;
			dwTime = GetTickCount();
		}
		if (dwTime + 300 < GetTickCount() && type == 2)
		{
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFireworksBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CFireworksBullet>(m_tInfo.matWorld, i, -1));
			}
			
			ck = true;
			dwTime = GetTickCount();
		}

	}

	if (dwTime + 1000 < GetTickCount())
	{
		ck = false;
		type = 1;
		count++;
	}
	if (count >= 4)
	{
		ck = true;
	}

	return count;
}

int CLMonster::OddBullet()
{
	static bool ck = false;
	static bool ck1 = false;
	static int type = 1;
	static int count = 0;
	if (count >= 4)
	{
		count = 0;
		ck = false;
		ck1 = false;
	}
	if (dwMonsterBullet + 100 < GetTickCount() && ck == false)
	{
		if (type == 1)
		{
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<COddBullet>(m_tInfo.matWorld, i, 1));
			}
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<COddBullet>(m_tInfo.matWorld, i, -1));
			}
			for (int i = 0; i < 16; ++i)
			{
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<COddBullet>(m_tInfo.matWorld, i, 2));
			}

			dwTime = GetTickCount();
			type = -1;
		}
		

	}

	if (dwMonsterBullet + 600 < GetTickCount() && ck1 == false)
	{
		CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CBasicBullet>(m_tInfo.matWorld, 1, 1));
		ck1 = true;
	}
	if (dwTime + 1300 < GetTickCount())
	{
		ck = false;
		ck1 = false;
		type = 1;
		count++;
	}
	if (count >= 4)
	{
		ck = true;
		ck1 = true;
	}

	return count;
}

int CLMonster::MonsterMove(int Dir)
{
	static int count = 0;
	static int ck = 0;
	if (ck == 1)
		ck = 0;
	switch (Dir)
	{
	case 1:
		m_tInfo.vPos += D3DXVECTOR3(-m_fSpeed, 0.f, 0.f);
		count++;
		break;
	case 2:
		m_tInfo.vPos += D3DXVECTOR3(0.f, -1, 0.f);
		count++;
		break;
	case 3:
		m_tInfo.vPos += D3DXVECTOR3(m_fSpeed, 0.f, 0.f);
		count++;
		break;
	case 4:
		m_tInfo.vPos += D3DXVECTOR3(0.f, 1, 0.f);
		count++;
		break;
	}
	if (count >= 60)
	{
		count = 0;
		ck = 1;
	}
	return ck;
}

void CLMonster::ZigZagPattern()
{
	if (Att == true)
	{
		if (ZigZagBullet() > 3)
		{
			Att = false;
			Move = true;
		}
	}
	if (Move == true && MonsterDir == 1)
	{
		if (MonsterMove(3) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 2;
		}
	}
	else if (Move == true && MonsterDir == 2)
	{
		if (MonsterMove(1) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 1;

		}
	}
}

void CLMonster::SpreadParentPattern()
{
	if (Att == true && MoveCount == 1)
	{
		if (SpreadBullet() > 3)
		{
			Att = false;
			Move = true;
		}
	}
	else if (Att == true && MoveCount == 0)
	{
		if (ParentBullet() > 3)
		{
			Att = false;
			Move = true;
		}
	}
	if (Move == true && MonsterDir == 1)
	{
		if (MonsterMove(3) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 2;
		}
	}
	else if (Move == true && MonsterDir == 2)
	{
		if (MonsterMove(1) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 1;

		}
	}

}

void CLMonster::FlowerPattern()
{
	if (Att == true)
	{
		if (FlowerBullet() > 3)
		{
			Att = false;
			Move = true;
		}
	}
	if (Move == true && MonsterDir == 1)
	{
		if (dwBasicTime + 100 < GetTickCount())
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CBasicBullet>(m_tInfo.matWorld, 1, 1));
			dwBasicTime = GetTickCount();
		}
		if (MonsterMove(3) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 2;
		}
	}
	else if (Move == true && MonsterDir == 2)
	{
		if (dwBasicTime + 100 < GetTickCount())
		{
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET, CreateBullet<CBasicBullet>(m_tInfo.matWorld, 1, 1));
			dwBasicTime = GetTickCount();
		}
		if (MonsterMove(1) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 1;

		}
	}
}

void CLMonster::FireworksOddPattern()
{
	if (Att == true && MoveCount == 1)
	{
		if (OddBullet() > 3)
		{
			Att = false;
			Move = true;
		}
	}
	else if (Att == true && MoveCount == 0)
	{
		if (FireworksBullet() > 3)
		{
			Att = false;
			Move = true;
		}
	}
	if (Move == true && MonsterDir == 1)
	{
		if (MonsterMove(3) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 2;
		}
	}
	else if (Move == true && MonsterDir == 2)
	{
		if (MonsterMove(1) == 1)
		{
			Move = false;
			Att = true;
			MoveCount++;
		}
		if (MoveCount == 2)
		{
			MoveCount = 0;
			MonsterDir = 1;

		}
	}
}

void CLMonster::Collision(CCollider * Collider)
{
	if (OBJID::PLAYER_BULLET == Collider->GetOwner()->GetId())
	{
		--m_iHp;
		if (0 >= m_iHp)
			m_bIsDead = true;
	}
}

CCollider * CLMonster::GetCollider()
{
	return m_pCollider;
}

int CLMonster::GetCurrentHp() const
{
	return m_iHp;
}

int CLMonster::GetMaxHp() const
{
	return m_iMaxHp;
}


OBJID::ID CLMonster::GetId()
{
	return OBJID::ENEMY;
}