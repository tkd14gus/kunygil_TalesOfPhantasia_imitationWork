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
		if (IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getAtt()) && _enemyManager->getMinion()[i]->getHitAtt() == true)
		{
			_enemyManager->getMinion()[i]->setHitAtt(false);
			if (_player->getAction() == pDEAD) {}
			else if (_player->getAction() == pGUARD) {}
			else if (_player->getAction() != pHIT)
			{
				_player->playerHit();
			}
		}
		//몬스터가 공격햇을때
		if (IntersectRect(&_rc, &_player->getPlayer()->attack, &_enemyManager->getMinion()[i]->getRect()) || _enemyManager->getMinion()[i]->getActionK() == eHIT)
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eHIT) 
			{
		
			}
			else
			{
				_player->hitPlayerAttK();
				_enemyManager->getMinion()[i]->setHpK(_enemyManager->getMinion()[i]->getHpK() - 1);
				if (_enemyManager->getMinion()[i]->getActionK() != eATTACK1 && _enemyManager->getMinion()[i]->getActionK() != eATTACK2 || _enemyManager->getMinion()[i]->getHpK()<1)
				{
					_enemyManager->getMinion()[i]->setCountK(0);
					_enemyManager->getMinion()[i]->setActionK(3);
				}
			}
		}
		//몬스터가 공격받앗을때
		else if (IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getRect()))
		{

			_enemyManager->getMinion()[i]->setCollision(true);
			if (_enemyManager->getMinion()[i]->getAttCountK() == _enemyManager->getMinion()[i]->getAttCd())
			{
				if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
				{
					_enemyManager->getMinion()[i]->setHitAtt(true);
					_enemyManager->getMinion()[i]->setCountK(0);
					_enemyManager->getMinion()[i]->setActionK(RANDOM->Range(4, 5));
				}
			}

		}
		//캐릭과 몬스터 충돌했을때
		else { _enemyManager->getMinion()[i]->setCollision(false); }



		if (_enemyManager->getMinion()[i]->getHpK() <= 0 && _enemyManager->getMinion()[i]->getCountK() > 20)
		{
			_enemyManager->removeMinion(i);

		}
		//몬스터 사망처리
	}
	if (_enemyManager->getMinion().empty() == true)
	{
		_player->playerWin();
	}

	//플레이어 승리처리
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
