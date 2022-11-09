#pragma once
#include "Obj.h"
#include "ColliderOwner.h"
#include "HpOwner.h"


class CCircleCollider;

class CFlang
	:public CObj, public ColliderOwner, public CHpOwner
{
public:
	explicit CFlang();
	virtual ~CFlang();
public:
	enum STATE
	{
		BACK, STAND, MOVELEFT, MOVERIGHT,MOVECENTER ,STATE_END
	};
	
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual OBJID::ID GetId() override;

	// ColliderOwner을(를) 통해 상속됨
	virtual void Collision(CCollider * Collider) override;
	virtual CCollider * GetCollider() override;
	
	void MoveCENTER();
	void CheckFrame();
	void UpdateFrame();
	void BulletPatern(PATERN pID);
	void Set_MOVELR() { MoveLR = 0; }
	void Set_Level()
	{
		if (m_bInvincibletime == false)
		{
			if (Level1 > 0)
				--Level1;
			if (Level1 == 0 && Level2 > 0)
				--Level2;
			if (Level1 == 0 && Level2 == 0 && Level3 > 0)
				--Level3;
		}
	}

private:
	D3DXVECTOR3 m_d3dxCenter;
	wstring m_wsImageKey;
	wstring m_wsStateKey[STATE_END];
	STATE m_eCurState;
	STATE m_eNextState;
	FRAME m_tFrame;
	DWORD dwPlayerBullet;
	PATERN PATERNID;
	CCircleCollider* m_pCollider;
	int MoveLR;
	D3DXMATRIX TEMPM;
	float magicangle;
	int Level1;
	int Level2;
	int Level3;
	int m_iHp;
	int m_iMaxHp;
	bool m_bInvincibletime;
	bool Switch1;
	bool Switch2;
	// CHpOwner을(를) 통해 상속됨
	virtual int GetCurrentHp() const override;
	virtual int GetMaxHp() const override;

};

