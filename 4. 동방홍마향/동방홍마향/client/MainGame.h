#pragma once

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
};

