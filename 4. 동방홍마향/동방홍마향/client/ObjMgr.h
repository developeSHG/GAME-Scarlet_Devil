#pragma once
class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)
private:
	CObjMgr();
	~CObjMgr();
public:
	void AddObject(OBJID::ID eID, CObj* pObj);

public:
	CObj* Get_Player() { return m_ObjList[OBJID::PLAYER].front(); }
	CObj* Get_Monster() { if (m_ObjList[OBJID::ENEMY].empty())return nullptr; else return m_ObjList[OBJID::ENEMY].front(); }
	list<CObj*>* GetObjList(OBJID::ID eID) { return &m_ObjList[eID]; }
public:
	int Update();
	void LateUpdate();
	void Render();
	void Release();
public:
	void DeleteID(OBJID::ID eID);
private:
	list<CObj*> m_ObjList[OBJID::END];

};
