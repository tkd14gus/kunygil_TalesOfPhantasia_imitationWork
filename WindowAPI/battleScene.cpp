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

	//만일 PLAYERDATA->getPlayerData()가 NULL이 아닐 때
	//(제일 먼저 켜지면 NULL로 초기화됨)
	//_player에 넣어준다.
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
		_subPlayer->checkDistanceWithEnemy(_enemyManager->getMinion()[i]->getEnemyX());	//몬스터와 서브 캐릭터 위치 측정
		
		
		if (_enemyManager->getMinion()[i]->getEnemyX() - _player->getPlayer()->x >0) //캐릭터가 왼쪽 몬스터가 오른쪽
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
			{
				_enemyManager->getMinion()[i]->setLeft(true);
			}
			
		}
		else if (_enemyManager->getMinion()[i]->getEnemyX() - (_player->getPlayer()->x + _player->getPlayer()->viewX) <= 0) // 몬스터가 오른쪽 캐릭터가 왼쪽
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
			{
				_enemyManager->getMinion()[i]->setLeft(false);
			}
		}
		//몬스터 좌우설정
		RECT _rc;
		if (IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getAtt()) && _enemyManager->getMinion()[i]->getHitAtt() == true)
		{
			if (_enemyManager->getMinion()[i]->getEnemyX() -(_player->getPlayer()->x + _player->getPlayer()->viewX) > 0) { _player->setSight(true); } //캐릭터왼쪽
			else { _player->setSight(false); } //캐릭터오른쪽
			_enemyManager->getMinion()[i]->setHitAtt(false);
			if (_player->getAction() == pDEAD) {}
			else if (_player->getAction() == pGUARD) {}
			else if (_player->getAction() != pHIT)
			{
				_player->playerHit();
			}
		}
		//아래 함수의 bool변수 자리에 _subPlayer->getArrowInfo()._rc랑 몹rc intersectRect 한 결과 넣어주세요
		_subPlayer->checkArrowHitTheEnemy(IntersectRect(&_rc, &_subPlayer->getArrowInfo(), &_enemyManager->getMinion()[i]->getRect()));

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
	_subPlayer->update();
	_enemyManager->update(_player->getPlayer()->viewX);

	//배틀상태가 아니라면(배틀이 끝났다면)
	if (!_player->getIsBattle())
	{
		//플레이어 정보도 저장해준다.
		PLAYERDATA->setPlayerData(_player);
		//화면을 바꿔준다.
		SCENEMANAGER->loadScene("게임화면");
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


	//프레임바디
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left, rc.top, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left, rc.bottom - (17 * scale), scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.bottom - (17 * scale), scale);
	//모서리


}  //렉트 내부에 그리는것 혹시쓸수도있어서 주석처리

