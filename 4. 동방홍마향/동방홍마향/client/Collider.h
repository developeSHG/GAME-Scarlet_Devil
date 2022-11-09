#pragma once

class CObj;
class CPointCollider;
class CLineCollider;
class CCircleCollider;
class CRectCollider;

class CCollider
{
public:
	enum class Tag
	{
		Point, Line, Circle, Rect
	};
public:
	explicit CCollider();
	virtual ~CCollider();
public:
	virtual Tag GetColliderTag() const = 0;
	virtual bool CheckHit(CPointCollider* Point) = 0;
	virtual bool CheckHit(CLineCollider* Line) = 0;
	virtual bool CheckHit(CCircleCollider* Circle) = 0;
	virtual bool CheckHit(CRectCollider* Rect) = 0;
public:
	inline void CCollider::SetOwner(CObj* pOwner) { m_pOwner = pOwner; }
	inline CObj* CCollider::GetOwner() const { return m_pOwner; }
	inline D3DXVECTOR3 CCollider::GetOffset() const { return m_Offset; }
	inline void CCollider::SetOffset(const D3DXVECTOR3& rOffset) { m_Offset = rOffset; }

protected:
	CObj* m_pOwner;
	D3DXVECTOR3 m_Offset;

};

