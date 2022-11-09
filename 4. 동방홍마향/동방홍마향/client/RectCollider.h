#pragma once
#include "Collider.h"

class CRectCollider :
	public CCollider
{
public:
	explicit CRectCollider();
public:
	virtual ~CRectCollider();
public:
	virtual Tag GetColliderTag() const override;
public:
	RectInfo GetColliderInfo() const;
	void SetColliderInfo(const RectInfo& ColliderInfo);

private:
	RectInfo m_tColliderInfo;

	// CCollider��(��) ���� ��ӵ�
	virtual bool CheckHit(CPointCollider * Point) override;
	virtual bool CheckHit(CLineCollider * Line) override;
	virtual bool CheckHit(CCircleCollider * Circle) override;
	virtual bool CheckHit(CRectCollider * Rect) override;
};

