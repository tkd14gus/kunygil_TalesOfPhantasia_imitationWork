#include "stdafx.h"
#include "bossScene.h"

HRESULT bossScene::init()
{

	_player = new player;
	_player->init();

	return S_OK;
}

void bossScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
}

void bossScene::update()
{
	_player->update();
}

void bossScene::render()
{
	_player->render();
}
