#pragma once
#include "Collider.h"

class CPointCollider :
	public CCollider
{
public:
	explicit CPointCollider();
public:
	virtual ~CPointCollider();

public:
	virtual Tag GetColliderTag() const override;

	virtual bool CheckHit(CPointCollider * Point) override;
	virtual bool CheckHit(CLineCollider * Line) override;
	virtual bool CheckHit(CCircleCollider * Circle) override;
	virtual bool CheckHit(CRectCollider * Rect) override;
};
