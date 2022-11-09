#pragma once

struct INFO
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 nvDir;
	D3DXVECTOR3 nvLook;
	D3DXVECTOR3 vSize;
	float fAngle;			// Degree
	D3DXMATRIX	matWorld;	// 월드행렬
};

struct TEX_INFO
{
	LPDIRECT3DTEXTURE9	pTexture;	// 불러온 텍스처을 제어하는 Com객체.
	D3DXIMAGE_INFO		tImgInfo;	// 불러온 텍스처의 정보
};

struct FRAME
{
	int iFrameStart;
	int iFrameEnd;
	int iFrameScene;
	DWORD dwFrameSpeed;
	DWORD dwFrameTime;
};


	struct CircleInfo
	{
		float fRadius;
		CircleInfo() : fRadius(0.f) {}
		CircleInfo(const float& _fRadius) : fRadius(_fRadius) {}
	};

	struct RectInfo
	{
		float fCX;
		float fCY;
		RectInfo() : fCX(0.f), fCY(0.f) {}
		RectInfo(const float& _fCX, const float& _fCY) : fCX(_fCX), fCY(_fCY) {}
	};
