#pragma once
#include "gameNode.h"
class inven :public gameNode
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();

	inven() {}
	~inven() {}
};


