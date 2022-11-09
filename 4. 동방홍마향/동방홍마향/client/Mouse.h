#pragma once
#include "Obj.h"
#include "ColliderOwner.h"

namespace kfgd
{
	class CMouse :
		public CObj, public ColliderOwner
	{
	public:
		CMouse();
		virtual ~CMouse();

		// CObj을(를) 통해 상속됨
		virtual void Initialize() override;
		virtual int Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Release() override;

		virtual void Collision(CCollider * Collider) override;
		virtual CCollider * GetCollider() override;

		virtual OBJID::ID GetId() override;
	private:
		CPointCollider* m_pCollider;
	};

}
