#include "stdafx.h"
#include "LineCollider.h"


CLineCollider::CLineCollider()
{
}


CLineCollider::~CLineCollider()
{
}

CCollider::Tag CLineCollider::GetColliderTag() const
{
	return Tag::Line;
}
