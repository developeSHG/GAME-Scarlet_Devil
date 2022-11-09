#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Collider.h"
#include "PointCollider.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "ColliderOwner.h"

CCollisionMgr::CCollisionMgr()
{
}
CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::DetectCollision(list<CObj*>* pDst, list<CObj*>* pSrc)
{
	for (CObj*& pDstObj : *pDst)
	{
		for (CObj*& pSrcObj : *pSrc)
		{
			ColliderOwner* pA = dynamic_cast<ColliderOwner*>(pDstObj);
			ColliderOwner* pB = dynamic_cast<ColliderOwner*>(pSrcObj);
			if (nullptr == pA || nullptr == pB)
				continue;
			if (nullptr == pA->GetCollider() || nullptr == pB->GetCollider())
				continue;
			bool bHit = false;
			switch (pB->GetCollider()->GetColliderTag())
			{
			case CCollider::Tag::Point:
				bHit = pA->GetCollider()->CheckHit(static_cast<CPointCollider*>(pB->GetCollider()));
				break;
			case CCollider::Tag::Line:
				bHit = pA->GetCollider()->CheckHit(static_cast<CLineCollider*>(pB->GetCollider()));
				break;
			case CCollider::Tag::Circle:
				bHit = pA->GetCollider()->CheckHit(static_cast<CCircleCollider*>(pB->GetCollider()));
				break;
			case CCollider::Tag::Rect:
				bHit = pA->GetCollider()->CheckHit(static_cast<CRectCollider*>(pB->GetCollider()));
				break;
			}
			if (bHit)
			{
				pA->Collision(pB->GetCollider());
				pB->Collision(pA->GetCollider());
			}
		}
	}
}
bool CCollisionMgr::CheckHit(CPointCollider * Point, CCircleCollider * Circle)
{
	D3DXVECTOR3 vWPosOfPoint;
	const D3DXMATRIX temp = Point->GetOwner()->Get_Info().matWorld;
	D3DXVec3TransformCoord(&vWPosOfPoint, &Point->GetOffset(), &Point->GetOwner()->Get_Info().matWorld);
	D3DXVECTOR3 vWPosOfCircle;
	const D3DXMATRIX temp2 = Circle->GetOwner()->Get_Info().matWorld;
	D3DXVec3TransformCoord(&vWPosOfCircle, &Circle->GetOffset(), &Circle->GetOwner()->Get_Info().matWorld);
	const float deltaX = vWPosOfPoint.x - vWPosOfCircle.x;
	const float deltaY = vWPosOfPoint.y - vWPosOfCircle.y;
	const float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	return Circle->GetColliderInfo().fRadius > distance;
}
bool CCollisionMgr::CheckHit(CCircleCollider * CircleA, CCircleCollider * CircleB)
{
	D3DXVECTOR3 vWPosOfCircleA;
	D3DXVec3TransformCoord(&vWPosOfCircleA, &CircleA->GetOffset(), &CircleA->GetOwner()->Get_Info().matWorld);
	D3DXVECTOR3 vWPosOfCircleB;
	D3DXVec3TransformCoord(&vWPosOfCircleB, &CircleB->GetOffset(), &CircleB->GetOwner()->Get_Info().matWorld);
	const float fRadiusSum = CircleA->GetColliderInfo().fRadius + CircleB->GetColliderInfo().fRadius;
	const float deltaX = vWPosOfCircleA.x - vWPosOfCircleB.x;
	const float deltaY = vWPosOfCircleA.y - vWPosOfCircleB.y;
	const float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	return fRadiusSum > distance;
}
bool CCollisionMgr::CheckHit(CCircleCollider * Circle, CRectCollider * Rect)
{
	D3DXVECTOR3 vWPosOfCircle;
	D3DXVec3TransformCoord(&vWPosOfCircle, &Circle->GetOffset(), &Circle->GetOwner()->Get_Info().matWorld);
	D3DXVECTOR3 vWPosOfRect;
	D3DXVec3TransformCoord(&vWPosOfRect, &Rect->GetOffset(), &Rect->GetOwner()->Get_Info().matWorld);
	const D3DXVECTOR3 LeftTopPointOfRect
	(
		vWPosOfRect.x - Rect->GetColliderInfo().fCX * 0.5f,
		vWPosOfRect.y - Rect->GetColliderInfo().fCY * 0.5f,
		0
	);
	const D3DXVECTOR3 RightBottomPointOfRect
	(
		vWPosOfRect.x + Rect->GetColliderInfo().fCX * 0.5f,
		vWPosOfRect.y + Rect->GetColliderInfo().fCY * 0.5f,
		0
	);
	if(
		(LeftTopPointOfRect.x < vWPosOfCircle.x && RightBottomPointOfRect.x > vWPosOfCircle.x)
		|| (LeftTopPointOfRect.y < vWPosOfCircle.y && RightBottomPointOfRect.y > vWPosOfCircle.y)
	)
	{
		const D3DXVECTOR3 LeftTopPointOfExtendedRect(
			LeftTopPointOfRect.x - Circle->GetColliderInfo().fRadius,
			LeftTopPointOfRect.y - Circle->GetColliderInfo().fRadius,
			0.f
		);
		const D3DXVECTOR3 RightBottomPointOfExtendedRect(
			RightBottomPointOfRect.x + Circle->GetColliderInfo().fRadius,
			RightBottomPointOfRect.y + Circle->GetColliderInfo().fRadius,
			0.f
		);
		if ((LeftTopPointOfExtendedRect.x < vWPosOfCircle.x && RightBottomPointOfExtendedRect.x > vWPosOfCircle.x)
			&& (LeftTopPointOfExtendedRect.y < vWPosOfCircle.y && RightBottomPointOfExtendedRect.y > vWPosOfCircle.y))
		{
			return true;
		}
	}
		else
		{
			// 사각형의 좌상단 점이 원안에 있을 경우
			if (IsPointInCircle(LeftTopPointOfRect, vWPosOfCircle, Circle->GetColliderInfo().fRadius))
				return true;
			// 사각형의 우상단 점이 원안에 있을 경우
			if (IsPointInCircle(RightBottomPointOfRect, vWPosOfCircle, Circle->GetColliderInfo().fRadius))
				return true;
			// 사각형의 좌하단 점이 원안에 있을 경우
			if (IsPointInCircle(LeftTopPointOfRect, vWPosOfCircle, Circle->GetColliderInfo().fRadius))
				return true;
			// 사각형의 우하단 점이 원안에 있을 경우
			if (IsPointInCircle(RightBottomPointOfRect, vWPosOfCircle, Circle->GetColliderInfo().fRadius))
				return true;
		}
		return false;
}
bool CCollisionMgr::IsPointInCircle(const D3DXVECTOR3 Point, const D3DXVECTOR3& PosOfCircle, const float& RadiusOfCircle)
{
	if (
		(Point.x >= PosOfCircle.x - RadiusOfCircle)
		&& (Point.x <= PosOfCircle.x + RadiusOfCircle)
		&& (Point.y >= PosOfCircle.y - RadiusOfCircle)
		&& (Point.y <= PosOfCircle.y + RadiusOfCircle)
		)
		return true;
	return false;
}
