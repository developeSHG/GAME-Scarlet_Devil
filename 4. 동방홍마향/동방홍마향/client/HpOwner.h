#pragma once
class CHpOwner
{
public:
	explicit CHpOwner() {};
	virtual ~CHpOwner() {};

public:
	virtual int GetCurrentHp() const = 0;
	virtual int GetMaxHp() const = 0;
};

