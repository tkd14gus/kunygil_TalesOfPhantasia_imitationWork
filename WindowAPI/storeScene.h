#pragma once
#include "gameNode.h"
class storeScene : public gameNode

{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();

	storeScene() {}
	~storeScene() {}

};

