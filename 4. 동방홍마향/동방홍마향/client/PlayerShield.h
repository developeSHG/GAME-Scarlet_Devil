#pragma once

#include "Obj.h"

class CPlayerShield :
	public CObj
{
public:
	CPlayerShield();
	virtual ~CPlayerShield();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
private:
	CObj* m_pPlayer;
};

