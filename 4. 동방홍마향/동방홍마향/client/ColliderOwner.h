#pragma once

class CCollider;

class ColliderOwner
{
public:
	explicit ColliderOwner() {}
public:
	virtual ~ColliderOwner() {}

public:
	virtual void Collision(CCollider* Collider) = 0;
	virtual CCollider* GetCollider() = 0;
};
