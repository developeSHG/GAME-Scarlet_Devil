#pragma once
#include "CEnemyPattern.h"
#include "ColliderOwner.h"
#include "Obj.h"

class CKRemilliaScarlet;
namespace kfgd
{
	class CKRmilliaPattern 
	{

	public:
		explicit CKRmilliaPattern(CKRemilliaScarlet* _pExecuter);
		virtual ~CKRmilliaPattern();

	public:
		void Initialize();
		void Update();
		void LateUpdate();

	private:
		void Release();

	private:
		CKRemilliaScarlet* m_pExecuter;
		vector<CEnemyPattern<CKRemilliaScarlet>*> m_listPattern;
		CEnemyPattern<CKRemilliaScarlet>* m_eCurPattern;

		class CBullet;

		class CBulletShooter
		{
		public:
			explicit CBulletShooter() {};
		public:
			virtual ~CBulletShooter() {};

		public:
			virtual CObj* Get_Shooter() = 0;
			virtual void BulletIsDead(CBullet* Bullet) = 0;
		};

		class CBullet :
			public CObj, public ColliderOwner
		{

		public:
			explicit CBullet();
			virtual ~CBullet();
			virtual OBJID::ID GetId() override;
			void SetAngle(float _fDegree);
			void SetSpeed(float _fSpeed);
			void SetShooter(CBulletShooter* Shooter);
			void SetLook(const D3DXVECTOR3& _LookVec);
			void SetDir(const D3DXVECTOR3& _DirVec);
			float GetAngle() const;
			virtual void Initialize() override;
			virtual int Update() override;
			virtual void LateUpdate() override;
			virtual void Release() override;
			virtual void Collision(CCollider * Collider) override;
		protected:
			bool OutOfRange() const;

		protected:
			float m_fSpeed;
			CBulletShooter* m_pShooter;
		};

		class CRedBullet_B :
			public CBullet
		{
		public:
			explicit CRedBullet_B();
			virtual ~CRedBullet_B();
			virtual void Initialize() override;
			virtual void LateUpdate() override;
			virtual void Render() override;
			virtual void Release() override;
			virtual CCollider * GetCollider() override;

		private:
			CCircleCollider* m_pCollider;
		};

		class CBlueBullet_M :
			public CBullet
		{
		public:
			explicit CBlueBullet_M();
			virtual ~CBlueBullet_M();
			virtual void Initialize() override;
			virtual void LateUpdate() override;
			virtual void Render() override;
			virtual void Release() override;
			virtual CCollider * GetCollider() override;
		private:
			CCircleCollider* m_pCollider;
		};

		class CBlueBullet_S :
			public CBullet
		{
		public:
			explicit CBlueBullet_S();
			virtual ~CBlueBullet_S();
			virtual void Initialize() override;
			virtual void Render() override;
			virtual CCollider * GetCollider() override;
		private:
			CCircleCollider* m_pCollider;

		};

		class CRedKnife :
			public CBullet
		{
		public:
			explicit CRedKnife();
			virtual ~CRedKnife();
			virtual void Initialize() override;
			virtual int Update() override;
			virtual void Render() override;
			virtual CCollider * GetCollider() override;
			void SetMatWorld(const D3DXMATRIX& _matWorld);
			void SetDirRight(bool _bRight);
		private:
			CCircleCollider* m_pCollider;
			bool m_bDirRight;
			bool m_bRevolve;
			float m_fDeltaAngle;
			D3DXMATRIX m_matWorld;
		};

		class CPatternA :
			public CEnemyPattern<CKRemilliaScarlet>
		{
		public:
			explicit CPatternA(CKRemilliaScarlet* _pExecuter);
			virtual ~CPatternA();

		public:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void LateUpdate() override;
			virtual bool IsRunning() const override;
			virtual bool CanRun() const override;

		private:
			DWORD m_dPreFinishTime;
			DWORD m_dCountOfFrame;
			float m_fAngle;
			static const DWORD SPEED_OF_PATTERN;

		};

		class CPatternB :
			public CEnemyPattern<CKRemilliaScarlet>, CBulletShooter
		{
		public:
			explicit CPatternB(CKRemilliaScarlet* _pExecuter);
			virtual ~CPatternB();

		public:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void LateUpdate() override;
			virtual bool IsRunning() const override;
			virtual bool CanRun() const override;
			CKRemilliaScarlet* GetExecuter() const;
		public:
			virtual void BulletIsDead(CBullet* Bullet) override;
			virtual CObj * Get_Shooter() override;

		private:
			DWORD m_dPreFinishTime;
			DWORD m_dCountOfFrame;
			list<CRedKnife*> m_listFeather;
			static const DWORD SPEED_OF_PATTERN;


		};
	};

}