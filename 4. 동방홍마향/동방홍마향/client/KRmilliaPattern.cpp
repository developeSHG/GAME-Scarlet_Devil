#include "stdafx.h"
#include "KRmilliaPattern.h"
#include "KRemilliaScarlet.h"
#include "CircleCollider.h"
#include "ObjMgr.h"

namespace kfgd
{

CKRmilliaPattern::CKRmilliaPattern(CKRemilliaScarlet* _pExecuter)
	: m_pExecuter(_pExecuter), m_eCurPattern(nullptr)
{
}


CKRmilliaPattern::~CKRmilliaPattern()
{
	Release();
}
void CKRmilliaPattern::Initialize()
{
	// ÅØ½ºÃÄ
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Bullet/Blue_M.png", L"Blue_M");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Bullet/Blue_S.png", L"Blue_S");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Bullet/Red_B.png", L"Red_B");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Bullet/Red_Feather.png", L"Red_Feather");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/RemilliaScarlet/Bullet/Red_Knife.png", L"Red_Knife");

	m_listPattern.emplace_back(new CPatternA(m_pExecuter));
	m_listPattern.emplace_back(new CPatternB(m_pExecuter));
}
void CKRmilliaPattern::Update()
{
	if (m_eCurPattern != nullptr)
	{

		if (m_eCurPattern->IsRunning())
		{
			m_eCurPattern->Update();
			return;
		}
		else
			m_eCurPattern = nullptr;
				
	}
	else
	{
		if (30 >= m_pExecuter->GetCurrentHp())
			m_eCurPattern = m_listPattern[1];
		else if (60 >= m_pExecuter->GetCurrentHp())
			m_eCurPattern = m_listPattern[0];	
		if(nullptr != m_eCurPattern)
			m_eCurPattern->Initialize();
	}
}
void CKRmilliaPattern::LateUpdate()
{
	if(nullptr != m_eCurPattern)
		m_eCurPattern->LateUpdate();
	if (30 >= m_pExecuter->GetCurrentHp() && m_eCurPattern == m_listPattern[0])
	{
		CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY_BULLET);
		m_eCurPattern = nullptr;
	}
	else if (0 >= m_pExecuter->GetCurrentHp() && m_eCurPattern == m_listPattern[1])
	{
		CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY_BULLET);
		m_eCurPattern = nullptr;
	}
}
void CKRmilliaPattern::Release()
{
	for (vector<CEnemyPattern<CKRemilliaScarlet>*>::iterator iter = m_listPattern.begin(); iter != m_listPattern.end(); )
	{
		SafeDelete(*iter);
		iter = m_listPattern.erase(iter);
	}
}

const DWORD CKRmilliaPattern::CPatternA::SPEED_OF_PATTERN = 30;

CKRmilliaPattern::CPatternA::CPatternA(CKRemilliaScarlet * _pExecuter)
	: CEnemyPattern(_pExecuter)
{
}
CKRmilliaPattern::CPatternA::~CPatternA()
{
}
void CKRmilliaPattern::CPatternA::Initialize()
{
	m_dCountOfFrame = 0;
	m_fAngle = 0.f;
}
void CKRmilliaPattern::CPatternA::Update()
{
	++m_dCountOfFrame;
	if (0 != m_dCountOfFrame % SPEED_OF_PATTERN)
		return;
	m_fAngle += 20;
	const D3DXVECTOR3 GlobalPosOfExecuter(m_pExecuter->Get_Info().matWorld._41, m_pExecuter->Get_Info().matWorld._42, m_pExecuter->Get_Info().matWorld._43);
	for (int i = 0; i < 5; ++i)
	{
		CRedBullet_B* RedBullet = new CRedBullet_B;
		RedBullet->Initialize();
		RedBullet->Set_Pos(GlobalPosOfExecuter);
		//RedBullet->SetAngle(m_fAngle + 72 * i);
		RedBullet->SetAngle(m_fAngle + 60 * i);
		RedBullet->SetSpeed(1.f);
		CObjMgr::GetInstance()->AddObject(RedBullet->GetId(),RedBullet);
	}
	for (int i = 0; i < 8; ++i)
	{
		CBlueBullet_M* BlueBullet = new CBlueBullet_M;
		BlueBullet->Initialize();
		BlueBullet->Set_Pos(GlobalPosOfExecuter);
		BlueBullet->SetAngle((m_fAngle+5) + 45 * i);
		BlueBullet->SetSpeed(1.2f);
		CObjMgr::GetInstance()->AddObject(BlueBullet->GetId(), BlueBullet);
	}
	for (int i = 0; i < 4; ++i)
	{
		CBlueBullet_S* BlueBullet = new CBlueBullet_S;
		BlueBullet->Initialize();
		BlueBullet->Set_Pos(GlobalPosOfExecuter);
		BlueBullet->SetAngle(30*((m_fAngle + 5) /20) + 8 * i);
		BlueBullet->SetSpeed(1.f);
		CObjMgr::GetInstance()->AddObject(BlueBullet->GetId(), BlueBullet);
	}
	if (false == IsRunning())
		m_dPreFinishTime = GetTickCount();
}
void CKRmilliaPattern::CPatternA::LateUpdate()
{
}
bool CKRmilliaPattern::CPatternA::IsRunning() const
{
	return m_fAngle <= 360.f;
}
bool CKRmilliaPattern::CPatternA::CanRun() const
{
	return m_dPreFinishTime + 5000 < GetTickCount();
}
CKRmilliaPattern::CRedBullet_B::CRedBullet_B()
	: m_pCollider(nullptr)
{
}
CKRmilliaPattern::CRedBullet_B::~CRedBullet_B()
{
	SafeDelete(m_pCollider);
}
void CKRmilliaPattern::CRedBullet_B::Initialize()
{
	CBullet::Initialize();
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(32.f));
}
void CKRmilliaPattern::CRedBullet_B::LateUpdate()
{

}
void CKRmilliaPattern::CRedBullet_B::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Red_B");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}
void CKRmilliaPattern::CRedBullet_B::Release()
{
}

CCollider * CKRmilliaPattern::CRedBullet_B::GetCollider()
{
	return m_pCollider;
}


CKRmilliaPattern::CBlueBullet_M::CBlueBullet_M()
	: m_pCollider(nullptr)
{
}

CKRmilliaPattern::CBlueBullet_M::~CBlueBullet_M()
{
	SafeDelete(m_pCollider);
}

void CKRmilliaPattern::CBlueBullet_M::Initialize()
{
	CBullet::Initialize();
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(14.f));
}
void CKRmilliaPattern::CBlueBullet_M::LateUpdate()
{
}
void CKRmilliaPattern::CBlueBullet_M::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Blue_M");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}
void CKRmilliaPattern::CBlueBullet_M::Release()
{
	
}

CCollider * CKRmilliaPattern::CBlueBullet_M::GetCollider()
{
	return m_pCollider;
}

CKRmilliaPattern::CBullet::CBullet()
	: m_pShooter(nullptr)
{

}

CKRmilliaPattern::CBullet::~CBullet()
{

}

OBJID::ID CKRmilliaPattern::CBullet::GetId()
{
	return OBJID::ENEMY_BULLET;
}
void CKRmilliaPattern::CBullet::SetAngle(float _fDegree)
{
	m_tInfo.fAngle = _fDegree;
}
void CKRmilliaPattern::CBullet::SetSpeed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
}
void CKRmilliaPattern::CBullet::SetShooter(CBulletShooter * Shooter)
{
	m_pShooter = Shooter;
}
void CKRmilliaPattern::CBullet::SetLook(const D3DXVECTOR3& _LookVec)
{
	m_tInfo.nvLook = _LookVec;
	D3DXVec3Normalize(&m_tInfo.nvLook, &m_tInfo.nvLook);
}
void CKRmilliaPattern::CBullet::SetDir(const D3DXVECTOR3 & _DirVec)
{
	m_tInfo.nvDir = _DirVec;
	D3DXVec3Normalize(&m_tInfo.nvDir, &m_tInfo.nvDir);
}
float CKRmilliaPattern::CBullet::GetAngle() const
{
	return m_tInfo.fAngle;
}
bool CKRmilliaPattern::CBullet::OutOfRange() const
{
	const D3DXVECTOR3 GlobalPos(m_tInfo.matWorld._41, m_tInfo.matWorld._42, m_tInfo.matWorld._43);
	//return (GlobalPos.x < 0 || GlobalPos.y < 0 || GlobalPos.x > WINCX - 200 || GlobalPos.y > WINCY);
	return (GlobalPos.x < 0 || GlobalPos.y < 0 || GlobalPos.x > 485 || GlobalPos.y > 570);
}
void CKRmilliaPattern::CBullet::Collision(CCollider * Collider)
{
	if (OBJID::PLAYER == Collider->GetOwner()->GetId())
	{
		m_bIsDead = true;
	}
}
void CKRmilliaPattern::CBullet::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.nvDir = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.nvLook = D3DXVECTOR3(0.f, -1.f, 0.f);
}
int CKRmilliaPattern::CBullet::Update()
{
	m_tInfo.vPos += m_tInfo.nvDir * m_fSpeed;

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

	if (OutOfRange() || m_bIsDead)
	{
		if (m_pShooter)
			m_pShooter->BulletIsDead(this);
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}
void CKRmilliaPattern::CBullet::LateUpdate()
{
}
void CKRmilliaPattern::CBullet::Release()
{
}
CKRmilliaPattern::CBlueBullet_S::CBlueBullet_S()
	: m_pCollider(nullptr)
{
}
CKRmilliaPattern::CBlueBullet_S::~CBlueBullet_S()
{
	SafeDelete(m_pCollider);
}
void CKRmilliaPattern::CBlueBullet_S::Initialize()
{
	CBullet::Initialize();
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(8.f));
}
void CKRmilliaPattern::CBlueBullet_S::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Blue_S");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}
CCollider * CKRmilliaPattern::CBlueBullet_S::GetCollider()
{
	return m_pCollider;
}

const DWORD CKRmilliaPattern::CPatternB::SPEED_OF_PATTERN = 30;

CKRmilliaPattern::CPatternB::CPatternB(CKRemilliaScarlet * _pExecuter)
	: CEnemyPattern<CKRemilliaScarlet>(_pExecuter)
{
}
CKRmilliaPattern::CPatternB::~CPatternB()
{
}
void CKRmilliaPattern::CPatternB::Initialize()
{
	m_dCountOfFrame = 0;
}

void CKRmilliaPattern::CPatternB::Update()
{
	++m_dCountOfFrame;
	
	if (0 != m_dCountOfFrame % SPEED_OF_PATTERN)
		return;
	if (0 == m_dCountOfFrame % (SPEED_OF_PATTERN * 5))
		return;
	const D3DXVECTOR3 GlobalPosOfExecuter(m_pExecuter->Get_Info().matWorld._41, m_pExecuter->Get_Info().matWorld._42, m_pExecuter->Get_Info().matWorld._43);
	const DWORD dCountOfPattern = m_dCountOfFrame / SPEED_OF_PATTERN;
	for (int i = 0; i < 12; ++i)
	{
		const float fDegree = 30 * i;

		CRedKnife* RedKnife = new CRedKnife;
		RedKnife->Initialize();
		RedKnife->Set_Pos(D3DXVECTOR3(0.f, 0.f, 0.f));
		RedKnife->SetAngle(fDegree);
		RedKnife->SetMatWorld(m_pExecuter->Get_Info().matWorld);
		RedKnife->SetSpeed(0.2f);
		RedKnife->SetDirRight(true);
		m_listFeather.push_back(RedKnife);
		CObjMgr::GetInstance()->AddObject(RedKnife->GetId(), RedKnife);
	}
	for (int i = 0; i < 12; ++i)
	{
		const float fDegree = 30 * i;

		CRedKnife* RedKnife = new CRedKnife;
		RedKnife->Initialize();
		RedKnife->Set_Pos(D3DXVECTOR3(0.f, 0.f, 0.f));
		RedKnife->SetAngle(-fDegree);
		RedKnife->SetMatWorld(m_pExecuter->Get_Info().matWorld);
		RedKnife->SetSpeed(0.2f);
		RedKnife->SetDirRight(false);
		m_listFeather.push_back(RedKnife);
		CObjMgr::GetInstance()->AddObject(RedKnife->GetId(), RedKnife);
	}

	if (false == IsRunning())
		m_dPreFinishTime = GetTickCount();
}
void CKRmilliaPattern::CPatternB::LateUpdate()
{
}
bool CKRmilliaPattern::CPatternB::IsRunning() const
{
	return m_dCountOfFrame <= SPEED_OF_PATTERN * 10;
	//return true;
}
bool CKRmilliaPattern::CPatternB::CanRun() const
{
	return m_dPreFinishTime + 10000 < GetTickCount();
}
CKRemilliaScarlet * CKRmilliaPattern::CPatternB::GetExecuter() const
{
	return m_pExecuter;
}
void CKRmilliaPattern::CPatternB::BulletIsDead(CBullet * Bullet)
{
	for (list<CRedKnife*>::iterator iter = m_listFeather.begin(); iter != m_listFeather.end(); ++iter)
	{
		if ((*iter) == Bullet)
		{
			m_listFeather.erase(iter);
			break;
		}
	}
}
CObj * CKRmilliaPattern::CPatternB::Get_Shooter()
{
	return m_pExecuter;
}
CKRmilliaPattern::CRedKnife::CRedKnife()
	: m_pCollider(nullptr), m_bRevolve(true), m_fDeltaAngle(0.f), m_bDirRight(true)
{
}
CKRmilliaPattern::CRedKnife::~CRedKnife()
{
	SafeDelete(m_pCollider);
}
void CKRmilliaPattern::CRedKnife::Initialize()
{
	CBullet::Initialize();
	m_pCollider = new CCircleCollider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetColliderInfo(CircleInfo(8.f));
}
int CKRmilliaPattern::CRedKnife::Update()
{
	if (m_bDirRight)
		++m_fDeltaAngle;
	else
	{
		--m_fDeltaAngle;
		m_tInfo.vSize.y = -1.f;
	}
	if (abs(m_fDeltaAngle) == 360 * 1)
	{
		m_bRevolve = false;
		m_tInfo.vPos.x = m_tInfo.matWorld._41;
		m_tInfo.vPos.y = m_tInfo.matWorld._42;
		m_tInfo.vPos.z = m_tInfo.matWorld._43;
	}

	if (m_bRevolve)
	{
		m_tInfo.vPos += D3DXVECTOR3(-1.f, 0.f, 0.f) * m_fSpeed;
		D3DXMATRIX matScale, matTranslate, matRevolveZ;
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matTranslate);
		D3DXMatrixIdentity(&matRevolveZ);

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
		D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
		D3DXMatrixRotationZ(&matRevolveZ, D3DXToRadian(m_tInfo.fAngle + m_fDeltaAngle));
		
		m_tInfo.matWorld = matScale * matTranslate * matRevolveZ * m_matWorld;
	}
	else
	{
		m_tInfo.vPos += m_tInfo.nvDir * (m_fSpeed + 1.f);
		D3DXMATRIX matScale, matRotateZ, matTranslate;
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matRotateZ);
		D3DXMatrixIdentity(&matTranslate);

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
		D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(m_tInfo.fAngle));
		D3DXMatrixTranslation(&matTranslate, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

		m_tInfo.matWorld = matScale * matRotateZ * matTranslate;
	}
	D3DXVec3TransformNormal(&m_tInfo.nvDir, &m_tInfo.nvLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.nvDir, &m_tInfo.nvDir);


	if (OutOfRange() || m_bIsDead)
	{
		if (m_pShooter)
			m_pShooter->BulletIsDead(this);
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}
void CKRmilliaPattern::CRedKnife::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Red_Knife");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}
CCollider * CKRmilliaPattern::CRedKnife::GetCollider()
{
	return m_pCollider;
}
void CKRmilliaPattern::CRedKnife::SetMatWorld(const D3DXMATRIX & _matWorld)
{
	m_matWorld = _matWorld;
}
void CKRmilliaPattern::CRedKnife::SetDirRight(bool _bRight)
{
	m_bDirRight = _bRight;
}
}
