#include "stdafx.h"
#include "RectCollider.h"


CRectCollider::CRectCollider()
{
}
CRectCollider::~CRectCollider()
{
}
CCollider::Tag CRectCollider::GetColliderTag() const
{
	return Tag::Rect;
}
RectInfo CRectCollider::GetColliderInfo() const
{
	return m_tColliderInfo;
}
void CRectCollider::SetColliderInfo(const RectInfo & ColliderInfo)
{
	m_tColliderInfo = ColliderInfo;
}
bool CRectCollider::CheckHit(CPointCollider * Point)
{
	return false;
}
bool CRectCollider::CheckHit(CLineCollider * Line)
{

	return false;
}
bool CRectCollider::CheckHit(CCircleCollider * Circle)
{
	return CCollisionMgr::CheckHit(Circle, this);
}
bool CRectCollider::CheckHit(CRectCollider * Rect)
{
	return false;
}
