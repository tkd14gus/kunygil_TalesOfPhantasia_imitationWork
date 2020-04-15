#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:
	RECT _rc[2];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	startScene() {}
	~startScene() {}
};

