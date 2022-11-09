#pragma once


class CScene
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual void Initialize() = 0;
	virtual int	 Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

