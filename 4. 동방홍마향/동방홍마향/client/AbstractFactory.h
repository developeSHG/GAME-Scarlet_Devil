#ifndef __ABSTRACTFACTORY
#define __ABSTRACTFACTORY
#pragma once

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateBullet(D3DXVECTOR3 vPos, float Angle=0)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		dynamic_cast<T*>(pObj)->Set_Angle(Angle);
		dynamic_cast<T*>(pObj)->Set_Pos(vPos);
		return pObj;
	}
	static CObj* CreateEBullet(PATERN pID,BULLET bid,D3DXVECTOR3 vPos, float Angle = 0)
	{
		CBullet* pBullet = new T(pID,bid);
		pBullet->Initialize();
		dynamic_cast<T*>(pBullet)->Set_Pos(vPos);
		dynamic_cast<T*>(pBullet)->Set_Angle(Angle);
		return pBullet;
	}
	static CObj* Create(int BulletType)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_BulletType(BulletType);
		return pObj;
	}
	static CObj* Create(D3DXMATRIX matWorld, int count, int BulletType)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_WorldMat(matWorld);
		pObj->Set_Count(count);
		pObj->Set_BulletType(BulletType);
		return pObj;
	}
	static CObj* Create(D3DXMATRIX matWorld)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_WorldMat(matWorld);
		pObj->Set_Count();
		return pObj;
	}
	static CObj* Create(D3DXVECTOR3 vPos)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(vPos);
		return pObj;
	}
	static CObj* Create(D3DXVECTOR3 vPos, int BulletType)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(vPos);
		pObj->Set_BulletType(BulletType);
		return pObj;
	}
	static CObj* Create(D3DXVECTOR3 vPos, float Angle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Angle(Angle);
		pObj->Set_Pos(vPos);
		return pObj;
	}


};
#endif // __ABSCRACTFACTORY
