#pragma once
#include "Collider.h"

class CLineCollider :
	public CCollider
{
public:
	explicit CLineCollider();
public:
	virtual ~CLineCollider();

public:
	virtual Tag GetColliderTag() const override;

};

