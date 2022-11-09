#pragma once
#include "Obj.h"
#include "CircleCollider.h"
#include "ColliderOwner.h"
class CParentBullet :
	public CObj, public ColliderOwner
{
public:
	CParentBullet();
	virtual ~CParentBullet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;

public:
	template<typename T>
	CObj* CreateBullet(D3DXMATRIX matWorld, int count, int type)
	{
		CObj* pBullet = CAbstractFactory<T>::Create(matWorld, count, type);
		return pBullet;
	}

public:
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;

private:
	DWORD dwTime;
	CCircleCollider* m_pCollider;
};

