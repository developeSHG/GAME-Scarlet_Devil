#include "stdafx.h"
#include "EBullet.h"
#include "Collider.h"
#include "Player.h"
#include "CircleCollider.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CEBullet::CEBullet()
{

}

CEBullet::CEBullet(PATERN pID, BULLET bID)
{
	bBounce = false;

	PaterID = pID;
	BulletID = bID;
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_iCoolTime = 0;
	switch (PaterID)
	{
	case GATLING:
		break;
	case SPREAD:
		break;
	case BOUNCE:
		bBounce = true;
		break;
	case PATERN_END:
		break;
	default:
		break;
	}

	switch (BulletID)
	{
	case REDSMALL:
		m_pCollider->SetColliderInfo(CircleInfo(3.f));
		break;
	case REDBIG:
		m_pCollider->SetColliderInfo(CircleInfo(5.f));
		break;
	case REDSNOW:
		m_pCollider->SetColliderInfo(CircleInfo(2.f));
		break;
	case BLUEBIG:
		break;
	case BLUESMALL:
		break;
	case BLUESNOW:
		break;
	case BULLET_END:
		break;
	default:
		break;
	}
}


CEBullet::~CEBullet()
{
	SafeDelete(m_pCollider);
}



void CEBullet::Initialize()
{
	m_wsStateKey[BULLET::REDSMALL] = L"REDSMALL";
	m_wsStateKey[BULLET::REDBIG] = L"REDBIG";
	m_wsStateKey[BULLET::REDSNOW] = L"REDSNOW";
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/REDSMALL.png", m_wsStateKey[BULLET::REDSMALL]);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/REDBIG.png", m_wsStateKey[BULLET::REDBIG]);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ENEMY/REDSNOW.png", m_wsStateKey[BULLET::REDSNOW]);
	m_fspeed = 2.f;

	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvDir = D3DXVECTOR3(1.f, 1.f, 0.f);
	fBombcount = 0;
}


int CEBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	fRadian = m_tInfo.fAngle  *D3DX_PI / 180;

	m_tInfo.vPos.x += cosf(fRadian)*m_fspeed;
	m_tInfo.vPos.y += -sinf(fRadian)*m_fspeed;
	D3DXMATRIX matScale, matRotateZ, matTranslate;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotateZ);
	D3DXMatrixIdentity(&matTranslate);

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);

	if (PaterID == BOUNCE)
		D3DXMatrixRotationZ(&matRotateZ, -fRadian); //z축회전 윈도우좌표시 sin고려 라디안값에 -곱하고주면됨
	else
		D3DXMatrixRotationZ(&matRotateZ, 0);

	D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

	m_tInfo.matWorld = matScale * matRotateZ * matTranslate;

	//내적D3DXVec3Dot
	//내적D3DXVec3Cross
	//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);//w가 1
	D3DXVec3TransformNormal(&m_tInfo.nvDir, &m_tInfo.nvDir, &m_tInfo.matWorld);//w가 0
	D3DXVec3Normalize(&m_tInfo.nvDir, &m_tInfo.nvDir);


	++fBombcount;
	return OBJ_NOEVENT;
}

void CEBullet::LateUpdate()
{
	if (bBounce == true)
	{
		if (m_tInfo.vPos.x <= 20)
		{
			m_tInfo.fAngle *= -1;
			m_tInfo.fAngle += 180;
			bBounce = false;
		}
		if (m_tInfo.vPos.x >= 480)
		{
			m_tInfo.fAngle *= -1;
			m_tInfo.fAngle += 180;
			bBounce = false;
		}
		if (m_tInfo.vPos.y <= 20)
		{
			m_tInfo.fAngle *= -1;
			bBounce = false;
		}
		if (m_tInfo.vPos.y >= 580)
		{
			m_bIsDead = true;
		}
	}
	else
	{
		if (m_tInfo.vPos.x <= 20 || m_tInfo.vPos.x >= 480 || m_tInfo.vPos.y <= 20 || m_tInfo.vPos.y >= 580)
			m_bIsDead = true;

		if (PaterID == GATLING)
		{
			if (fBombcount == 200)
			{
				m_bIsDead = true;
				for(int i=0;i<6;++i)
				CObjMgr::GetInstance()->AddObject(OBJID::ENEMY_BULLET,
					CAbstractFactory<CEBullet>::CreateEBullet(PATERN::SPREAD, BULLET::REDSMALL, m_tInfo.vPos,i*60.f));
			}
		}

	}

}

void CEBullet::Render()
{

	const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsStateKey[BulletID]);
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		test->pTexture,
		0,
		&D3DXVECTOR3(test->tImgInfo.Width / 2.f, test->tImgInfo.Height / 2.f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);


}

void CEBullet::Release()
{

}

OBJID::ID CEBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}

void CEBullet::Collision(CCollider * Collider)
{
	if (Collider->GetOwner()->GetId() == OBJID::PLAYER)
	{
		m_bIsDead = true;
		cout << "충돌" << endl;
		//dynamic_cast<CPlayer*>(Collider->GetOwner())->LoseLife();
	}
}

CCollider * CEBullet::GetCollider()
{
	return m_pCollider;
}