#include "stdafx.h"
#include "battleScene.h"

HRESULT battleScene::init()
{
	_player = new player;
	_player->init();
	_enemyManager = new enemyManager;
	_enemyManager->init();

	return S_OK;
}

void battleScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void battleScene::update()
{
	for (int i = 0; i < _enemyManager->getMinion().size(); i++)
	{
		RECT _rc;

		if (IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getRect()))
		{
			
			_enemyManager->getMinion()[i]->setCollision(true);
			if (_enemyManager->getMinion()[i]->getAttCountK() == 250 && _enemyManager->getMinion()[i]->getActionK() == eIDLE)
			{
				_enemyManager->getMinion()[i]->setActionK(RANDOM->Range(4, 5));
			}

		}
		else { _enemyManager->getMinion()[i]->setCollision(false); }
			
	}

	_player->update();
	_enemyManager->update();
}

void battleScene::render()
{
	_player->render();
	_enemyManager->render();
	char str[32];
	sprintf(str, "%d,%d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 100, 650, str, strlen(str));
}
