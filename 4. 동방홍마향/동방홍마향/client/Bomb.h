#pragma once
#include "Obj.h"
#include "ColliderOwner.h"


class CCircleCollider;
class CBomb :
	public CObj , public ColliderOwner
{
public:
	CBomb();

	virtual ~CBomb();
public:
	void Set_Pos(D3DXVECTOR3 Pos) { m_tInfo.vPos = Pos; }
	void Set_Angle(float Angle) { m_tInfo.fAngle = Angle; }
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;

	
private:
	int m_iBombCount;
	float m_fSize;
	CCircleCollider* m_pCollider;

};

