#pragma once

#include "Obj.h"

class CPlayerShield :
	public CObj
{
public:
	CPlayerShield();
	virtual ~CPlayerShield();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
private:
	CObj* m_pPlayer;
};

