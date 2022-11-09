#pragma once
#include "Obj.h"
#include "ColliderOwner.h"

class CCircleCollider;

class CGuideBullet :
	public CObj , public ColliderOwner
{
public:
	CGuideBullet();
	virtual ~CGuideBullet();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual OBJID::ID GetId() override;
private:
	CObj* m_pMonster;
	CObj* m_pPlayer;
	float fMonsterX;

	// ColliderOwner��(��) ���� ��ӵ�
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;
	CCircleCollider* m_pCollider;

};

