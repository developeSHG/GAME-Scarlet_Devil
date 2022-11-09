#pragma once
#include "Obj.h"

class CHpOwner;
class CBossUI
	: public CObj
{
public:
	explicit CBossUI();
public:
	virtual ~CBossUI();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
	void SetHpOwner(CHpOwner* _pHpOwner);
private:
	CHpOwner* m_pHpOwner;
	wstring m_wsEnemyImageKey;
	wstring m_wsHpBarImageKey;
	
};

