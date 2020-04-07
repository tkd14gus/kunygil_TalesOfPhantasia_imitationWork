#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_rocket = IMAGEMANAGER->addImage("rocket", "Images/rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));
	//�÷��̾� ��Ʈ
	//_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 52, 64);

	//ü�¹� �յ��̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("progressBarFront", "progressBarFront.bmp", 50, 10);
	IMAGEMANAGER->addImage("progressBarBack", "progressBarBack.bmp", 50, 10);



	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missile;
	_missile->init(10, 500);

	//��ź Ŭ���� �ʱ�ȭ
	_bomb = new bomb;
	_bomb->init(5, 600);

	//ü�¹� Ŭ���� �ʱ�ȭ
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack");
	//���� �ʱ�ȭ
	_maxHp = _currentHp = 100;
	


	return S_OK;
}

void player::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);

	//��ź Ŭ���� ����
	_bomb->release();
	SAFE_DELETE(_bomb);

	//ü�¹� Ŭ���� ����
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void player::update()
{
	//�÷��̾� �����̱� & ȭ������� ������ ���ϰ� �����
	if (INPUT->GetKey(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (INPUT->GetKey(VK_RIGHT) && _rocket->getX() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);
	}
	//�Ѿ˹߻�
	if (INPUT->GetKeyDown(VK_SPACE))
	{
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//��ź�߻�
	if (INPUT->GetKeyDown('B'))
	{
		_bomb->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//�̻��� Ŭ���� ������Ʈ
	_missile->update();
	//��ź Ŭ���� ������Ʈ
	_bomb->update();
	//�浹�Լ�
	this->collision();

	//ü�¹� ������Ʈ
	_hpBar->update();
	//ü�¹� ��ġ, ���뵵 ������Ʈ ����� �Ѵ�
	_hpBar->setPos(_rocket->getX(), _rocket->getY() - 20);
	_hpBar->setGauge(_maxHp, _currentHp);


	//�÷��̾� �����ͷ� ���̺� �ε�
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		this->save();
	}
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		this->load();
	}

}

void player::render()
{
	//�÷��̾� ����
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);
	
	//�̻��� Ŭ���� ����
	_missile->render();

	//��ź Ŭ���� ����
	_bomb->render();

	//ü�¹� Ŭ���� ����
	_hpBar->render();

}
//��ź����
void player::removeBomb(int index)
{
	_bomb->removeBomb(index);
}

//�浹�Լ�(�÷��̾��Ѿ�, �̴Ͼ��浹)
void player::collision()
{
	for (int i = 0; i < _bomb->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_bomb->getBullet()[i].rc,
				&_em->getMinion()[j]->getRect()))
			{
				_bomb->removeBomb(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

}
//������
void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::save()
{
	PLAYERDATA->setHp(_currentHp);
}

void player::load()
{
	_currentHp = PLAYERDATA->getHp();
}
