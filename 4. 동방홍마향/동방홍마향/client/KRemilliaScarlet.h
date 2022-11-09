#pragma once
#include "Obj.h"
#include "ColliderOwner.h"
#include "KRmilliaPattern.h"
#include "HpOwner.h"

class CRectCollider;

class CKRemilliaScarlet :
	public CObj, public ColliderOwner, public CHpOwner
{
private:
	enum STATE
	{
		STAND, MOVE, STATE_END
	};

public:
	explicit CKRemilliaScarlet();

public:
	virtual ~CKRemilliaScarlet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;

	virtual OBJID::ID GetId() override;

private:
	void CheckFrame();
	FRAME_STATE UpdateFrame();

public:
	virtual int GetCurrentHp() const override;
	virtual int GetMaxHp() const override;

private:
	int m_iMaxHealth;
	int m_iHealth;

private:
	wstring m_wsImageKey;
	wstring m_wsStateKey[STATE_END];
	STATE m_eCurState;
	STATE m_eNextState;
	FRAME m_tFrame;

private:
	CRectCollider* m_pCollider;

private:
	kfgd::CKRmilliaPattern Pattern;

};

