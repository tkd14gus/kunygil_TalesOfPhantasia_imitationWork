#pragma once
#include "singletonBase.h"

class playerData : public singletonBase <playerData>
{
private:
	int _hp;
	float _x, _y;

public:
	HRESULT init();
	void release();

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	playerData() {}
	~playerData() {}
};

