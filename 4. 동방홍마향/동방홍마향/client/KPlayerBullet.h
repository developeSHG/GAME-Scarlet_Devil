#pragma once
#include "Bullet.h"
#include "ColliderOwner.h"


class CKPlayerBullet :
	public CBullet, public ColliderOwner
{
public:

	explicit CKPlayerBullet();
	virtual ~CKPlayerBullet();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
public:
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;



	
};

