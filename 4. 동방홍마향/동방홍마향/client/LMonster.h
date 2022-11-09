#pragma once
#include "Obj.h"
#include "ColliderOwner.h"
#include "CircleCollider.h"
#include "HpOwner.h"

class CLMonster :
	public CObj, public ColliderOwner, public CHpOwner
{
private:
	enum STATE
	{
		HORIZON, VERTICAL, STATE_END
	};
	
public:
	CLMonster();
	virtual ~CLMonster();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;
public:
	void CheckFrame();
	FRAME_STATE UpdateFrame();

public:
	int ZigZagBullet();
	int SpreadBullet();
	int FlowerBullet();
	int ParentBullet();
	int FireworksBullet();
	int OddBullet();

public:
	int MonsterMove(int Dir);
	void ZigZagPattern();
	void SpreadParentPattern();
	void FlowerPattern();
	void FireworksOddPattern();

public:
	template<typename T>
	CObj* CreateBullet(D3DXMATRIX matWorld, int count, int type)
	{
		CObj* pBullet = CAbstractFactory<T>::Create(matWorld, count, type);
		return pBullet;
	}


private:
	wstring m_wsImageKey;
	wstring m_wsStateKey[STATE_END];
	STATE m_eCurState;
	STATE m_eNextState;
	FRAME m_tFrame;
	DWORD dwMonsterBullet;
	DWORD dwMonsterMove;
	DWORD dwTime;
	DWORD dwBasicTime;
	int m_eDir;
	float m_fSpeed;
	bool Move;
	bool Att;
	int MoveCount;
	int MonsterDir;
	

	int m_iHp;
	int m_iMaxHp;

private:
	CCircleCollider* m_pCollider;

public:
	// ColliderOwner을(를) 통해 상속됨
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;

	virtual int GetCurrentHp() const override;
	virtual int GetMaxHp() const override;
};

