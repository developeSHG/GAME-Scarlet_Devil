#pragma once

struct INFO
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 nvDir;
	D3DXVECTOR3 nvLook;
	D3DXVECTOR3 vSize;
	float fAngle;			// Degree
	D3DXMATRIX	matWorld;	// �������
};

struct TEX_INFO
{
	LPDIRECT3DTEXTURE9	pTexture;	// �ҷ��� �ؽ�ó�� �����ϴ� Com��ü.
	D3DXIMAGE_INFO		tImgInfo;	// �ҷ��� �ؽ�ó�� ����
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
