#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


HRESULT enemyManager::init()
{
	//미니언 생성, 보스, 일반몬스터
	//따로 함수로 빼서 처리하면 관리및 보기에 편하다

	//미니언 생성
	this->setMinion();
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

void enemyManager::update()
{
	//총알 업데이트
	//_bullet->update();

	//벡터에 담긴 미니언들 업데이트
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update();
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

void enemyManager::setMinion()
{
	for (int i = 0; i < ENEMYAMOUNT; i++)
	{
		if (i == 0)
		{
			minionXPos.push_back(RANDOM->Range(950, 1000));
		}
		if (i > 0)
		{
			minionXPos.push_back(RANDOM->Range(minionXPos[i - 1] + 50, minionXPos[i - 1] + 150));
		}
		//minionXPos.push_back(rand() % WINSIZEX / 2 + WINSIZEX / 2 - 50);
		//위치 안겹치게
		//100은 대략적인 거리 수치입니다
		//if (i != 0 && minionXPos[i] - minionXPos[i - 1] < -100 && minionXPos[i] - minionXPos[i - 1] > 100) {
		//	i--;
		//	continue;
		//}
		enemy* _minion = new golem;
		_minion->init(PointMake(minionXPos[i], 500));
		_vMinion.push_back(_minion);
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
