#pragma once
namespace kfgd
{
	template<typename T>
	class CEnemyPattern
	{
	public:
		explicit CEnemyPattern(T* _pExecuter) : m_pExecuter(_pExecuter) {}
		virtual ~CEnemyPattern() {};

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual bool IsRunning() const = 0;
		virtual bool CanRun() const = 0;

	protected:
		T* m_pExecuter;
	};
}