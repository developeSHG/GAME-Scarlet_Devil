#pragma once
#include "Obj.h"
#include "CircleCollider.h"
#include "ColliderOwner.h"
class CZigZagBullet :
	public CObj, public ColliderOwner
{
public:
	CZigZagBullet();
	virtual ~CZigZagBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
private:
	CCircleCollider* m_pCollider;

public:
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;
};

