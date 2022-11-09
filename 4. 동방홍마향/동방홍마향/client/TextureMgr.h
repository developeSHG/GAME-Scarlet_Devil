#pragma once
class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)
private:
	CTextureMgr();
	~CTextureMgr();

public:
	const TEX_INFO* FindTexture(const wstring& rImageKey, const wstring& wstrStateKey = L"", const int& iIndex = 0);
public:
	void InsertTexture(const wstring& rFilePath, const wstring& rImageKey, const wstring& wstrStateKey = L"", const int& iCount = 0);

public:
	void Release();
private:
	map<const wstring, CTexture*> m_mapTexture;
};

