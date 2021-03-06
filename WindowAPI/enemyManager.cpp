#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


HRESULT enemyManager::init(int battleCount)
{
	//미니언 생성, 보스, 일반몬스터
	//따로 함수로 빼서 처리하면 관리및 보기에 편하다

	//미니언 생성
	this->setMinion(battleCount);
	//보스생성
	//this->setBoss();

	//총알 클래스 초기화
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release()
{
	//총알 클래스 삭제
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(int playerViewX)
{
	//총알 업데이트
	//_bullet->update();

	//벡터에 담긴 미니언들 업데이트
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update(playerViewX);
	}

	//미니언 총알발사
	//this->minionBulletFire();

	//충돌함수
	this->collision();
}

void enemyManager::render()
{
	//총알클래스 렌더
	//_bullet->render();

	//벡터에 담긴 미니언들 렌더
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->render();
	}
}

void enemyManager::setMinion(int battleCount)
{

	if (battleCount != 4)
	{
		int ran = RANDOM->Range(3);
		for (int j = 0; j < ran; j++)
		{
			enemy* _minion = new golem;
			_minion->init(PointMake(RANDOM->Range(1100, 1300) + j * RANDOM->Range(100, 200), 500));
			_vMinion.push_back(_minion);
		}
		ran = RANDOM->Range(1, 5);
		for (int j = 0; j < ran; j++)
		{
			enemy* _minion = new mummy;
			_minion->init(PointMake(RANDOM->Range(950, 1000) + j * RANDOM->Range(50, 100), 500));
			_vMinion.push_back(_minion);
		}
	}
	else
	{
		enemy* _minion = new jamir;
		_minion->init(PointMake(RANDOM->Range(950, 1000), 500));
		_vMinion.push_back(_minion);
		
		// enemy* _gminion = new golem;								//골렘소환테스트
		// _gminion->init(PointMake(minionXPos[i], 500));
		// _vMinion.push_back(_gminion);
	}

}

void enemyManager::setBoss() {

}

void enemyManager::minionBulletFire()
{
	/*
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//int a = 10;
		//int* p = &a;
		//cout << p << endl; //a의 주소
		//cout << *p << endl; //a의 값
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -(PI_2), 3.0f);
		}
	}*/
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

void enemyManager::collision()
{
	//RECT rc;
	//for (int i = 0; i < ENEMYAMOUNT; i++) {
	//	if (IntersectRect(&rc, &_player->getRCPlayer(), &getMinion()[i]->getRect())) {
	//		//적 개체 멈추기
	//		getMinion()[i]->setCollision(true);
	//		//위치재설정
	//		_player->setRCPlayerLeft(getMinion()[i]->getRect().right);
	//		//플레이어 피통깎기
	//		_player->hitDamage(5);
	//	}
	//}
}
