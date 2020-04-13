#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


HRESULT enemyManager::init()
{
	//�̴Ͼ� ����, ����, �Ϲݸ���
	//���� �Լ��� ���� ó���ϸ� ������ ���⿡ ���ϴ�

	//�̴Ͼ� ����
	this->setMinion();
	//��������
	//this->setBoss();

	//�Ѿ� Ŭ���� �ʱ�ȭ
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release()
{
	//�Ѿ� Ŭ���� ����
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	//�Ѿ� ������Ʈ
	//_bullet->update();

	//���Ϳ� ��� �̴Ͼ�� ������Ʈ
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update();
	}

	//�̴Ͼ� �Ѿ˹߻�
	//this->minionBulletFire();

	//�浹�Լ�
	this->collision();
}

void enemyManager::render()
{
	//�Ѿ�Ŭ���� ����
	//_bullet->render();

	//���Ϳ� ��� �̴Ͼ�� ����
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
		//��ġ �Ȱ�ġ��
		//100�� �뷫���� �Ÿ� ��ġ�Դϴ�
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
		//cout << p << endl; //a�� �ּ�
		//cout << *p << endl; //a�� ��
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
	//		//�� ��ü ���߱�
	//		getMinion()[i]->setCollision(true);
	//		//��ġ�缳��
	//		_player->setRCPlayerLeft(getMinion()[i]->getRect().right);
	//		//�÷��̾� ������
	//		_player->hitDamage(5);
	//	}
	//}
}
