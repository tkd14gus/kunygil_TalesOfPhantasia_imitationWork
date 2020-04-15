#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class battleScene : public gameNode
{
private:
	player* _player;				//�÷��̾� Ŭ����
	subplayer* _subPlayer;			//�����÷��̾� Ŭ����
	enemyManager* _enemyManager;	//���Ŵ��� Ŭ����
	RECT _statusBox;
	RECT _enemyBox;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void frameBoxRender(RECT rc, float scale);			//�������ִ³��̶�����

	battleScene() {}
	~battleScene() {}
};

