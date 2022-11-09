#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_bIsDead(FALSE)
	,m_iBulletType(0)
	, count(1)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}


CObj::~CObj()
{
}
