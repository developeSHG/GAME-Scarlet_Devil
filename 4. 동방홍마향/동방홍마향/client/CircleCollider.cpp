#include "stdafx.h"
#include "CircleCollider.h"


CCircleCollider::CCircleCollider()
{
}


CCircleCollider::~CCircleCollider()
{
}

CCollider::Tag CCircleCollider::GetColliderTag() const
{
	return Tag::Circle;
}

CircleInfo CCircleCollider::GetColliderInfo() const
{
	return m_tColliderInfo;
}

void CCircleCollider::SetColliderInfo(const CircleInfo & ColliderInfo)
{
	m_tColliderInfo = ColliderInfo;
}

bool CCircleCollider::CheckHit(CPointCollider * Point)
{
	return CCollisionMgr::CheckHit(Point, this);
}

bool CCircleCollider::CheckHit(CLineCollider * Line)
{
	return false;
}

bool CCircleCollider::CheckHit(CCircleCollider * Circle)
{
	return CCollisionMgr::CheckHit(this, Circle);
}

bool CCircleCollider::CheckHit(CRectCollider * Rect)
{
	return CCollisionMgr::CheckHit(this, Rect);
}
