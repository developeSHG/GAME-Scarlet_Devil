#pragma once
#include "ColliderOwner.h"
#include "Obj.h"

class CCircleCollider;

class CPlayer :
	public ColliderOwner , public CObj
{
private:
	enum STATE
	{
		HORIZON, VERTICAL, STATE_END
	};

public:
	explicit CPlayer();
	virtual ~CPlayer();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;

private:
	void KeyInput();
	void CheckFrame();
	FRAME_STATE UpdateFrame();


public:
	template<typename T>
	CObj* CreateBullet(D3DXVECTOR3 vPos, float Angle = 0)
	{
		CObj* pBullet = CAbstractFactory<T>::CreateBullet(vPos, Angle);
		return pBullet;
	}
	template<typename T>
	CObj* CreateBullet(D3DXVECTOR3 vPos, int BulletType)
	{
		CObj* pBullet2 = CAbstractFactory<T>::Create(vPos, BulletType);
		return pBullet2;
	}
	template<typename T>
	CObj* CreateShield(int BulletType)
	{
		CObj* pShield = CAbstractFactory<T>::Create(BulletType);
		return pShield;
	}

public:
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;


public:
	void LoseLife() { --m_iLife; }



private:
	wstring m_wsImageKey;
	wstring m_wsStateKey[STATE_END];
	STATE m_eCurState;
	STATE m_eNextState;
	FRAME m_tFrame;
	DWORD dwPlayerBullet;
	int m_iLife;
	CCircleCollider* m_pCollider;

};

