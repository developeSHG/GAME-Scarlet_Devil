#include "stdafx.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEX_INFO * CTextureMgr::FindTexture(const wstring & rImageKey, const wstring & wstrStateKey, const int & iIndex)
{
	map<const wstring, CTexture*>::iterator iter = m_mapTexture.find(rImageKey);
	if (m_mapTexture.end() == iter)
		return nullptr;
	if(0 == wstrStateKey.length())
		return iter->second->GetTexInfo();
	else
		return iter->second->GetTexInfo(wstrStateKey, iIndex);
	
}

void CTextureMgr::InsertTexture(const wstring & rFilePath, const wstring & rImageKey, const wstring & wstrStateKey, const int & iCount)
{
	map<const wstring, CTexture*>::iterator iter = m_mapTexture.find(rImageKey);
	if (iter == m_mapTexture.end())
	{
		CTexture* Texture = nullptr;
		if (0 == wstrStateKey.length())
			Texture = new CSingleTexture;
		else
			Texture = new CMultiTexture;
		
		HRESULT hr = Texture->LoadTexture(rFilePath, wstrStateKey, iCount);
		FAILED_CHECK_RETURN(hr);
		m_mapTexture.emplace(rImageKey, Texture);
	}
	else
	{
		if (0 != wstrStateKey.length())
		{
			HRESULT hr = iter->second->LoadTexture(rFilePath, wstrStateKey, iCount);
			FAILED_CHECK_RETURN(hr);
		}
	}
}

void CTextureMgr::Release()
{
	for (auto& pPair : m_mapTexture)
	{
		if (pPair.second)
		{
			delete pPair.second;
			pPair.second = nullptr;
		}
	}
	m_mapTexture.clear();
}
