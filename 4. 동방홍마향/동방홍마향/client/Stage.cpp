#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Mouse.h"
#include "Flang.h"
#include "LMonster.h"
#include "KRemilliaScarlet.h"

CStage::CStage()
{
}


CStage::~CStage()
{
}

void CStage::Initialize()
{
	D3DXMatrixIdentity(&m_matWorld);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Back.png", L"Back");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/STAGE/Stage_1.png", L"Stage1");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Bullet/PlayerBullet.png", L"PlayerBullet");

	kfgd::CMouse* Mouse = new kfgd::CMouse;
	Mouse->Initialize();
	CObjMgr::GetInstance()->AddObject(OBJID::MOUSE, Mouse);

	CPlayer* Player = new CPlayer;
	Player->Initialize();
	CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, Player);
	
	//CFlang* Flang = new CFlang;
	//Flang->Initialize();
	//CObjMgr::GetInstance()->AddObject(OBJID::ENEMY,Flang);
	//CLMonster* pMonster = new CLMonster;
	//pMonster->Initialize();
	//CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pMonster);
	//CKRemilliaScarlet* Scarlet = new CKRemilliaScarlet;
	//Scarlet->Initialize();
	//CObjMgr::GetInstance()->AddObject(Scarlet->GetId(), Scarlet);
}

int CStage::Update()
{
	CObjMgr::GetInstance()->Update();
	if (CKeyMgr::GetInstance()->KeyDown(VK_F1))
	{
		CFlang* Flang = new CFlang;
		Flang->Initialize();
		CObjMgr::GetInstance()->AddObject(Flang->GetId(), Flang);		
	}
	if (CKeyMgr::GetInstance()->KeyUp(VK_F1))
	{

	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_F2))
	{
		CLMonster* pMonster = new CLMonster;
		pMonster->Initialize();
		CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pMonster);
	}
	if (CKeyMgr::GetInstance()->KeyUp(VK_F2))
	{
	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_F3))
	{
		CKRemilliaScarlet* Scarlet = new CKRemilliaScarlet;
		Scarlet->Initialize();
		CObjMgr::GetInstance()->AddObject(Scarlet->GetId(), Scarlet);
	}
	if (CKeyMgr::GetInstance()->KeyUp(VK_F3))
	{

	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_F4))
	{
		CObjMgr::GetInstance()->DeleteID(OBJID::UI);
		CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY_BULLET);
		CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY);
	}
	if (CKeyMgr::GetInstance()->KeyUp(VK_F4))
	{

	}

	return 0;
}

void CStage::LateUpdate()
{
	CCollisionMgr::DetectCollision(CObjMgr::GetInstance()->GetObjList(OBJID::ID::PLAYER_BULLET), 
		CObjMgr::GetInstance()->GetObjList(OBJID::ID::ENEMY));
	CCollisionMgr::DetectCollision(CObjMgr::GetInstance()->GetObjList(OBJID::ID::ENEMY_BULLET),
		CObjMgr::GetInstance()->GetObjList(OBJID::ID::PLAYER));
	CCollisionMgr::DetectCollision(CObjMgr::GetInstance()->GetObjList(OBJID::ID::BOMB),
		CObjMgr::GetInstance()->GetObjList(OBJID::ID::ENEMY_BULLET));
	
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage::Render()
{
	
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Back");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	
	D3DXMATRIX TEMP{};
	D3DXMatrixIdentity(&TEMP);
	TEMP(3, 0) = 20;
	TEMP(3, 1) = 20;
	const TEX_INFO* Stage = CTextureMgr::GetInstance()->FindTexture(L"Stage1");
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&TEMP);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		Stage->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);


	CObjMgr::GetInstance()->Render();
}

void CStage::Release()
{
	CObjMgr::GetInstance()->DeleteID(OBJID::PLAYER);
	CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY);
	CObjMgr::GetInstance()->DeleteID(OBJID::ENEMY);
}
