#pragma once
#include "Bullet.h"
#include "ColliderOwner.h"
class CEBullet :
	public CBullet, public ColliderOwner
{
public:
	CEBullet();
	CEBullet(PATERN pID,BULLET bID);
	virtual ~CEBullet();
	
	// CBullet을(를) 통해 상속됨
	virtual OBJID::ID GetId() override;
	// ColliderOwner을(를) 통해 상속됨
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	wstring m_wsStateKey[BULLET_END];
	BULLET BulletID;
	PATERN PaterID;
	float m_fspeed;
	float fDotAngle;
	float fRadian;
	float fBombcount;
	int m_iCoolTime;
	bool bBounce;
};

