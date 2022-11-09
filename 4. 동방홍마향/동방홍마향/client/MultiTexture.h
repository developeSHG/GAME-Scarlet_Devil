#pragma once
#include "Texture.h"
class CMultiTexture :
	public CTexture
{
public:
	explicit CMultiTexture();

public:
	virtual ~CMultiTexture();

	// CTexture을(를) 통해 상속됨
	virtual const TEX_INFO * GetTexInfo(const wstring & wstrStateKey = L"", const int & iIndex = 0) override;
	virtual HRESULT LoadTexture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	map<const wstring, vector<TEX_INFO*>*> m_mapVecTexInfo;
};

