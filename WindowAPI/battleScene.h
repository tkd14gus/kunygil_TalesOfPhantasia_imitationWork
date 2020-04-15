#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class battleScene : public gameNode
{
private:
	player* _player;				//플레이어 클래스
	subplayer* _subPlayer;			//서브플레이어 클래스
	enemyManager* _enemyManager;	//적매니져 클래스
	RECT _statusBox;
	RECT _enemyBox;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void frameBoxRender(RECT rc, float scale);			//맵툴에있는놈이랑같음

	battleScene() {}
	~battleScene() {}
};

