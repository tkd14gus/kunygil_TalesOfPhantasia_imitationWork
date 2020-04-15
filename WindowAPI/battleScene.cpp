#include "stdafx.h"
#include "battleScene.h"

HRESULT battleScene::init()
{
	_player = new player;
	_player->init();
	_subPlayer = new subplayer;
	_subPlayer->init();
	_enemyManager = new enemyManager;
	_statusBox = RectMake(0, 500, 380, 250);
	_enemyBox = RectMake(380, 500, 220, 250);

	mummy = golem = 0;


	//만일 PLAYERDATA->getPlayerData()가 NULL이 아닐 때
	//(제일 먼저 켜지면 NULL로 초기화됨)
	//_player에 넣어준다.
	if (PLAYERDATA->getPlayerData() != NULL)
	{
		_player = PLAYERDATA->getPlayerData();

	}
	if (PLAYERDATA->getSubPlayerData() != NULL)
	{
		_subPlayer = PLAYERDATA->getSubPlayerData();
	}

	_subPlayer->setSubPlayerXY(200, 414);

	_enemyManager->init(_player->getBattleCount());

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
	mummy = 0;
	golem = 0;
	jamirHp = 0;

	for (int i = 0; i < _enemyManager->getMinion().size(); i++)
	{
		if (_enemyManager->getMinion()[i]->getEnemyType() == JAMIR) { jamirHp = _enemyManager->getMinion()[i]->getHpK(); }
		else if (_enemyManager->getMinion()[i]->getEnemyType() == MUMMY) { mummy++; }
		else if (_enemyManager->getMinion()[i]->getEnemyType() == GOLEM) { golem++; }
		_subPlayer->checkDistanceWithEnemy(_enemyManager->getMinion()[i]->getEnemyX());	//몬스터와 서브 캐릭터 위치 측정
		
		
		if (_enemyManager->getMinion()[i]->getEnemyX() - (_player->getPlayer()->x + _player->getPlayer()->viewX) >0) //캐릭터가 왼쪽 몬스터가 오른쪽
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
			{
				if (_enemyManager->getMinion()[i]->getEnemyType() == JAMIR && _enemyManager->getMinion()[i]->getActionK() == eWALK) {}
				else { _enemyManager->getMinion()[i]->setLeft(true); }
			}
			
		}
		else if (_enemyManager->getMinion()[i]->getEnemyX() - (_player->getPlayer()->x + _player->getPlayer()->viewX) <= 0) // 몬스터가 오른쪽 캐릭터가 왼쪽
		{
			if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
			{
				if(_enemyManager->getMinion()[i]->getEnemyType() == JAMIR && _enemyManager->getMinion()[i]->getActionK() == eWALK){ }
				else { _enemyManager->getMinion()[i]->setLeft(false); }
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
				if (_enemyManager->getMinion()[i]->getActionK() == eATTACK2&& _enemyManager->getMinion()[i]->getEnemyType() == JAMIR)
				{
					_enemyManager->getMinion()[i]->setHpK(_enemyManager->getMinion()[i]->getHpK() + 1);
				}
				else { _enemyManager->getMinion()[i]->setHpK(_enemyManager->getMinion()[i]->getHpK() - 1); }
				if (_enemyManager->getMinion()[i]->getActionK() != eATTACK1 && _enemyManager->getMinion()[i]->getActionK() != eATTACK2 || _enemyManager->getMinion()[i]->getHpK()<1)
				{
					_enemyManager->getMinion()[i]->setCountK(0);
					_enemyManager->getMinion()[i]->setActionK(3);
				}
			}
		}
		//몬스터가 공격받앗을때
		else if (_enemyManager->getMinion()[i]->getEnemyType() == JAMIR && _enemyManager->getMinion()[i]->getAttCountK() == _enemyManager->getMinion()[i]->getAttCd() && _enemyManager->getMinion()[i]->getActionK() == eIDLE)
		{
			if (_enemyManager->getMinion()[i]->getHpK() > _enemyManager->getMinion()[i]->getHpMax() / 2)
			{
					_enemyManager->getMinion()[i]->setHitAtt(true);
			_enemyManager->getMinion()[i]->setActionK(2);
			}
			else
			{
				int a;
				a = RANDOM->Range(1, 2);
				if (a == 1)
				{
					_enemyManager->getMinion()[i]->setHitAtt(true);
					_enemyManager->getMinion()[i]->setActionK(2);
				}
				else if (a == 2)
				{
					_enemyManager->getMinion()[i]->setActionK(5);
				}
			}
		}
		else if (IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getRect()))
		{

			if (_enemyManager->getMinion()[i]->getEnemyType() == JAMIR)
			{
				_enemyManager->getMinion()[i]->setCollision(true);
				if (_enemyManager->getMinion()[i]->getAttCountK() < _enemyManager->getMinion()[i]->getAttCd())
				{
					if (_enemyManager->getMinion()[i]->getAttCountK() % 50 == 0)
					{
						_enemyManager->getMinion()[i]->setHitAtt(true);
						_enemyManager->getMinion()[i]->setActionK(4);
					}

				}
				
			}
			else
			{
				_enemyManager->getMinion()[i]->setCollision(true);
				if (_enemyManager->getMinion()[i]->getAttCountK() == _enemyManager->getMinion()[i]->getAttCd())
				{
					if (_enemyManager->getMinion()[i]->getActionK() == eIDLE || _enemyManager->getMinion()[i]->getActionK() == eWALK)
					{
						_enemyManager->getMinion()[i]->setHitAtt(true);
						_enemyManager->getMinion()[i]->setCountK(0);

						{ _enemyManager->getMinion()[i]->setActionK(RANDOM->Range(4, 5)); }
					}
				}
			}
		}
		//캐릭과 몬스터 충돌했을때
		//else { _enemyManager->getMinion()[i]->setCollision(false); }
		if (!IntersectRect(&_rc, &_player->getPlayer()->rc, &_enemyManager->getMinion()[i]->getRect())) { _enemyManager->getMinion()[i]->setCollision(false); }
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
	_subPlayer->update(_player->getPlayer()->viewX);
	_enemyManager->update(_player->getPlayer()->viewX);

	//배틀상태가 아니라면(배틀이 끝났다면)
	if (!_player->getIsBattle())
	{
		//플레이어 정보도 저장해준다.
		PLAYERDATA->setPlayerData(_player);
		PLAYERDATA->setSubPlayerData(_subPlayer);
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
	
	IMAGEMANAGER->findImage("Thp")->render(getMemDC(), 312, 520);
	
	IMAGEMANAGER->findImage("Tcress")->render(getMemDC(), 30, 550);
	NumberRender(330, 550, _player->getPlayer()->hp);

	IMAGEMANAGER->findImage("Tchester")->render(getMemDC(), 30, 590);
	NumberRender(330, 590, _subPlayer->getSubPlayer()->hp);
	if (mummy != 0) 
	{ 
		IMAGEMANAGER->findImage("Tmummy")->render(getMemDC(), 410, 540);
		NumberRender(560, 540, mummy);
	}

	if (mummy == 0 && golem != 0)
	{
		IMAGEMANAGER->findImage("Tgolem")->render(getMemDC(), 410, 540);
		NumberRender(560, 540, golem);
	}
	else if(mummy != 0 && golem != 0)
	{
		IMAGEMANAGER->findImage("Tgolem")->render(getMemDC(), 410, 580); 
		NumberRender(560, 580, golem);
	}

	if (jamirHp != 0)
	{
		IMAGEMANAGER->findImage("Tjamir")->render(getMemDC(), 450, 530);
		IMAGEMANAGER->findImage("Thp")->render(getMemDC(), 410, 575);
		NumberRender(550, 575, jamirHp);
	}
	_subPlayer->render();
}

void battleScene::NumberRender(int x, int y, int hp)
{
	int a = x;
	int b;
		//char str[32];
		for (int i = 1; i < 10000; i *= 10)
		{
			if (hp < i) { break; }
			b = (hp / i) % 10;
			IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), a, y, b, 0);
			a -= 16;

		}
	
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

