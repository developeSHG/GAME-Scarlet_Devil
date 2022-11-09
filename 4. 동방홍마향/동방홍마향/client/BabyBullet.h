#pragma once
#include "Obj.h"
#include "CircleCollider.h"
#include "ColliderOwner.h"

class CBabyBullet :
	public CObj, public ColliderOwner
{
public:
	CBabyBullet();
	virtual ~CBabyBullet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
private:
	DWORD dwTime;
	CObj* m_pPlayer;
	CCircleCollider* m_pCollider;


public:
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;

};

