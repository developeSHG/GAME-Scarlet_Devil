#pragma once
#include "Obj.h"

class CCircleCollider;

class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	// CObj��(��) ���� ��ӵ�
	void Set_Angle(float Angle) {m_tInfo.fAngle = Angle;}
protected:
	CCircleCollider* m_pCollider;

};

