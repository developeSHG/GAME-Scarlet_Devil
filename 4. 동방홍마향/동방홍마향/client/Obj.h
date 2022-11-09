#pragma once


class CObj
{
public:
	explicit CObj();
	virtual ~CObj();

public:
	const INFO& Get_Info(void)const { return m_tInfo; }
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	virtual OBJID::ID GetId() = 0;
	void Set_Dead() { m_bIsDead = true; }
	void Set_Pos(D3DXVECTOR3 vPos)
	{
		m_tInfo.vPos = vPos;
	}
	void Set_WorldMat(D3DXMATRIX matWorld) { ParentWorldMat = matWorld; }
	void Set_BulletType(int BulletType) { m_iBulletType = BulletType; }
	void Set_Count(int cnt) { count = cnt; }
protected:
	INFO m_tInfo;
	bool m_bIsDead;
	int m_iBulletType;
	int count;
	D3DXMATRIX ParentWorldMat;
};

