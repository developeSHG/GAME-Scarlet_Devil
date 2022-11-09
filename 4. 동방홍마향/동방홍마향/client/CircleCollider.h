#pragma once
#include "Collider.h"

class CCircleCollider :
	public CCollider
{
public:
	explicit CCircleCollider();
public:
	virtual ~CCircleCollider();

public:
	virtual Tag GetColliderTag() const override;

public:
	CircleInfo GetColliderInfo() const;
	void SetColliderInfo(const CircleInfo& ColliderInfo);

private:
	CircleInfo m_tColliderInfo;

public:
	virtual bool CheckHit(CPointCollider * Point) override;
	virtual bool CheckHit(CLineCollider * Line) override;
	virtual bool CheckHit(CCircleCollider * Circle) override;
	virtual bool CheckHit(CRectCollider * Rect) override;
};

//inline CircleInfo CCircleCollider::GetColliderInfo() const { return m_tColliderInfo; }
//void CCircleCollider::SetColliderInfo(const CircleInfo& ColliderInfo) { m_tColliderInfo = ColliderInfo; }

