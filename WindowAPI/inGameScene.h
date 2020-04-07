#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class inGameScene : public gameNode
{
private:
	player* _player; //�÷��̾� Ŭ����
	enemyManager* _enemyManager;	//���Ŵ��� Ŭ����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	inGameScene() {}
	~inGameScene() {}
};

