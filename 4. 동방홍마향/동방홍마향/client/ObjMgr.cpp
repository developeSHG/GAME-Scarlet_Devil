#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(OBJID::ID eID, CObj * pObj)
{
	m_ObjList[eID].emplace_back(pObj);
}

int CObjMgr::Update()
{

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (list<CObj*>::iterator& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				delete *iter;
				*iter = nullptr;
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->LateUpdate();
			if (m_ObjList[i].empty())
				break;
		}
	}
}

void CObjMgr::Render()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Render();
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			if (pObj)
			{
				delete pObj;
				pObj = nullptr;
			}
		}
		m_ObjList[i].clear();
	}
}

void CObjMgr::DeleteID(OBJID::ID eID)
{
	for (auto& pObj : m_ObjList[eID])
	{
		SafeDelete(pObj);
	}
	m_ObjList[eID].clear();
}
