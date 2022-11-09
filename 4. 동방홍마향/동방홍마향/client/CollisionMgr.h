#pragma once

class CObj;
class CPointCollider;
class CLineCollider;
class CCircleCollider;
class CRectCollider;

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();
	static bool CheckCollisionSphere(CObj * pDst, CObj * pSrc);
	static void CollisionSphere(CObj * pPlayer, list<CObj*> pSrc);
	static void DetectCollision(list<CObj*>* pDst, list<CObj*>* pSrc);
	
	static bool CheckHit(CPointCollider* Point, CCircleCollider* Circle);
	static bool CheckHit(CCircleCollider* CircleA, CCircleCollider* CircleB);
	static bool CheckHit(CCircleCollider* Circle, CRectCollider* Rect);

	static bool IsPointInCircle(const D3DXVECTOR3 Point, const D3DXVECTOR3& PosOfCircle, const float& RadiusOfCircle);
};

