#include "stdafx.h"
#include "battleScene.h"

HRESULT battleScene::init()
{
	_player = new player;
	_player->init();
	_subPlayer = new subplayer;
	_subPlayer->init();
	_enemyManager = new enemyManager;
	_enemyManager->init();
	_statusBox = RectMake(0, 500, 380, 250);
	_enemyBox = RectMake(380, 500, 220, 250);

	//���� PLAYERDATA->getPlayerData()�� NULL�� �ƴ� ��
	//(���� ���� ������ NULL�� �ʱ�ȭ��)
	//_player�� �־��ش�.
	if (PLAYERDATA->getPlayerData() != NULL)
	{
		_player = PLAYERDATA->getPlayerData();

	}
	return S_OK;
}

void battleScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
	_subPlayer->release();
	SAFE_DELETE(_subPlayer);
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void battleScene::update()
{
	_subPlayer->checkDistanceWithPlayer(_player->getPlayer()->x);

	for (int i = 0; i < _enemyManager->getMinion().size(); i++)
	{
		_subPlayer->checkDistanceWithEnemy(_enemyManager->getMinion()[i]->getEnemyX());	//���Ϳ� ���� ĳ���� ��ġ ����
		
		
		if (_enemyManager->getMinion()[i]->getEnemyX() - _player->getPlayer()->x >0) //ĳ���Ͱ� ���� ���Ͱ� ������
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
			{
				_enemyManager->getMinion()[i]->setLeft(true);
			}
			
		}
		else if (_enemyManager->getMinion()[i]->getEnemyX() - (_player->getPlayer()->x + _player->getPlayer()->viewX) <= 0) // ���Ͱ� ������ ĳ���Ͱ� ����
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
			{
				_enemyManager->getMinion()[i]->setLeft(false);
			}
		}
		//���� �¿켳��
		RECT _rc;
		if (IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getAtt()) && _enemyManager->getMinion()[i]->getHitAtt() == true)
		{
			if (_enemyManager->getMinion()[i]->getEnemyX() -(_player->getPlayer()->x + _player->getPlayer()->viewX) > 0) { _player->setSight(true); } //ĳ���Ϳ���
			else { _player->setSight(false); } //ĳ���Ϳ�����
			_enemyManager->getMinion()[i]->setHitAtt(false);
			if (_player->getAction() == pDEAD) {}
			else if (_player->getAction() == pGUARD) {}
			else if (_player->getAction() != pHIT)
			{
				_player->playerHit();
			}
		}
		//�Ʒ� �Լ��� bool���� �ڸ��� _subPlayer->getArrowInfo()._rc�� ��rc intersectRect �� ��� �־��ּ���
		_subPlayer->checkArrowHitTheEnemy(IntersectRect(&_rc, &_subPlayer->getArrowInfo(), &_enemyManager->getMinion()[i]->getRect()));

		//���Ͱ� ����������
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
		//���Ͱ� ���ݹ޾�����
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
		//ĳ���� ���� �浹������
		else { _enemyManager->getMinion()[i]->setCollision(false); }

		if (_enemyManager->getMinion()[i]->getHpK() <= 0 && _enemyManager->getMinion()[i]->getCountK() > 20)
		{
			_enemyManager->removeMinion(i);

		}
		//���� ���ó��
	}
	if (_enemyManager->getMinion().empty() == true)
	{
		_player->playerWin();
	}

	//�÷��̾� �¸�ó��
	_player->update();
	_subPlayer->update();
	_enemyManager->update(_player->getPlayer()->viewX);

	//��Ʋ���°� �ƴ϶��(��Ʋ�� �����ٸ�)
	if (!_player->getIsBattle())
	{
		//�÷��̾� ������ �������ش�.
		PLAYERDATA->setPlayerData(_player);
		//ȭ���� �ٲ��ش�.
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

void battleScene::render()
{
	//IMAGEMANAGER->findImage("commonbattlebg")->render(getMemDC(), 0, 0, _player->getPlayer()->viewX, 0, WINSIZEX, 433);
	//IMAGEMANAGER->findImage("commonbattle")->render(getMemDC(), 0, 0, (float)_player->getPlayer()->viewX*1.5F, 0, WINSIZEX,500);
	//
	IMAGEMANAGER->findImage("bossbattlebg")->render(getMemDC(), 0, 0, _player->getPlayer()->viewX, 0, WINSIZEX, 433);
	IMAGEMANAGER->findImage("bossbattle")->render(getMemDC(), 0, 0, (float)_player->getPlayer()->viewX*1.5F, 0, WINSIZEX, 500);
	_player->render();
	_enemyManager->render();
	frameBoxRender(_statusBox, 1.0f);
	frameBoxRender(_enemyBox, 1.0f);
	
	//char str[32];
	//sprintf(str, "%d,%d", _ptMouse.x, _ptMouse.y);
	//TextOut(getMemDC(), 100, 650, str, strlen(str));
	_subPlayer->render();
}

void battleScene::frameBoxRender(RECT rc, float scale)
{
	IMAGEMANAGER->findImage("accountbox")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, rc.right - rc.left, rc.bottom - rc.top,1.0f);
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, rc.right - rc.left, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left, rc.top + rc.bottom - rc.top - (17 * scale), 0, 0, rc.right - rc.left, 17 * scale, scale);


	//�����ӹٵ�
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left, rc.top, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left, rc.bottom - (17 * scale), scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.bottom - (17 * scale), scale);
	//�𼭸�


}  //��Ʈ ���ο� �׸��°� Ȥ�þ������־ �ּ�ó��

