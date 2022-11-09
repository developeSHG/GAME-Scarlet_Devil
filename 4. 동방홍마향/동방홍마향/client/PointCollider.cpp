#include "stdafx.h"
#include "PointCollider.h"


CPointCollider::CPointCollider()
{
}
CPointCollider::~CPointCollider()
{
}
CCollider::Tag CPointCollider::GetColliderTag() const
{
	return Tag::Point;
}
bool CPointCollider::CheckHit(CPointCollider * Point)
{
	return false;
}
bool CPointCollider::CheckHit(CLineCollider * Line)
{
	return false;
}
bool CPointCollider::CheckHit(CCircleCollider * Circle)
{
	return CCollisionMgr::CheckHit(this, Circle);
}
bool CPointCollider::CheckHit(CRectCollider * Rect)
{
	return false;
}
