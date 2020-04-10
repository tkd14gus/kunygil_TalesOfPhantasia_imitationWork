#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(POINT position)
{
	//������ ���� �ʱ�ȭ
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//�̹��� �ҷ�����(1)
	_imageIdle = IMAGEMANAGER->findImage("mummyIdle");
	_imageWalk = IMAGEMANAGER->findImage("mummyWalk");
	_imageHit = IMAGEMANAGER->findImage("mummyHit");
	_imageAttack1 = IMAGEMANAGER->findImage("mummyAttack1");
	_imageAttack2 = IMAGEMANAGER->findImage("mummyAttack2");
	_imageGuard = IMAGEMANAGER->findImage("mummyGuard");
	_imageDead = IMAGEMANAGER->findImage("mummyDead");

	//�� ��ü ���� ��ġ
	_state =IDLE;
	playerX = position.x;
	playerY = position.y;
	playerWidth = _imageIdle->getWidth() - 125;
	playerheight = _imageIdle->getHeight() - 20;
	_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	

	//#====================================================================================================
	//#				���ʿ� �ҷ��� �̹����� �ӽ��Դϴ�
	//#				���õ� �� Ÿ�Կ� ���� �ٸ� �̹����� �����ϴ�(�̹����� ��� �����)
	//#				���ʿ��� �ҷ��� �׸�(*�̹��� �ҷ�����(1) �׸�)�� �Ʒ� �׸��� �����Ǹ� ����ϴ�
	//#=====================================================================================================
	/*
	type = rand() % 3; //�� Ÿ�� �������� �����ϱ�
	switch (type)
	{
	case MUMMY:
		_imageIdle = IMAGEMANAGER->findImage("mummyIdle");
		_imageWalk = IMAGEMANAGER->findImage("mummyWalk");
		_imageHit = IMAGEMANAGER->findImage("mummyHit");
		_imageAttack1 = IMAGEMANAGER->findImage("mummyAttack1");
		_imageAttack2 = IMAGEMANAGER->findImage("mummyAttack2");
		_imageGuard = IMAGEMANAGER->findImage("mummyGuard");
		_imageDead = IMAGEMANAGER->findImage("mummyDead");
		_rc = RectMakeCenter(position.x, position.y, _image->getWidth()-50, _image->getHeight());
		break;
	case GOLEM:
		_image = IMAGEMANAGER->findImage("----");
		_rc = RectMakeCenter(position.x, position.y, _image->getWidth()-50, _image->getHeight());
		break;
	case ETC:
		_image = IMAGEMANAGER->findImage("----");
		_rc = RectMakeCenter(position.x, position.y, _image->getWidth()-50, _image->getHeight());
		break;
	}*/

	collision = false;

	//�������� �Ѿ� ��Ÿ�� �ִ� ���� �ʱ�ȭ
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{

	switch (_state) {
	case IDLE:
		playerWidth = _imageIdle->getWidth() - 125;
		playerheight = _imageIdle->getHeight() - 20;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	case WALK:
		playerWidth = _imageIdle->getWidth() - 90;
		playerheight = _imageIdle->getHeight() - 20;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	case HIT:
		playerWidth = _imageIdle->getWidth() - 95;
		playerheight = _imageIdle->getHeight() - 20;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	case ATTACK1:
		//ĳ���� ���� �þ�� ���� ��Ʈ�� �þ�� �����Ϸ��� (1)�� ���� �����ߴµ� ��ġ ������ �� �� ���Ƽ� �ϴ� �׽��ϴ� 
		//(1) playerWidth ++;
		playerWidth = _imageIdle->getWidth() - 60;
		playerheight = _imageIdle->getHeight() - 20;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	case ATTACK2:
		playerWidth = _imageIdle->getWidth() - 60;
		playerheight = _imageIdle->getHeight()-5;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	case GUARD:
		playerWidth = _imageIdle->getWidth() - 90;
		playerheight = _imageIdle->getHeight() - 20;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	case DEAD:
		playerWidth = _imageIdle->getWidth() - 70;
		playerheight = _imageIdle->getHeight() - 20;
		_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
		break;
	}

	this->move();
	this->animation();
}

void enemy::render()
{
	this->draw();
	
}

void enemy::move()
{
	//�÷��̾�� �浹���� ���� ��� ����
	switch (collision)
	{
	case true:
		_state = IDLE;
		break;
	case false:
		_state = WALK;
		break;
	}

	//���¿� ���� �̵���
	switch (_state) {
	case WALK:
		playerX--;
		break;
	case HIT:
		break;
	case ATTACK1:
		break;
	case ATTACK2:
		break;
	}
}

void enemy::draw()
{
	Rectangle(getMemDC(), _rc);
	switch (_state) {
	case IDLE:
		_imageIdle->render(getMemDC(), _rc.left - 105, _rc.top - 20);
		break;
	case WALK:
		_imageWalk->frameRender(getMemDC(), _rc.left - 75, _rc.top - 20);
		break;
	case HIT:
		_imageHit->render(getMemDC(), _rc.left - 85, _rc.top - 20);
		break;
	case ATTACK1:
		_imageAttack1->frameRender(getMemDC(), _rc.left - 105, _rc.top - 20);
		break;
	case ATTACK2:
		_imageAttack2->frameRender(getMemDC(), _rc.left - 60, _rc.top - 5);
		break;
	case GUARD:
		_imageGuard->render(getMemDC(), _rc.left - 70, _rc.top - 20);
		break;
	case DEAD:
		_imageDead->render(getMemDC(), _rc.left - 43, _rc.top - 20);
		break;
	}	
}

void enemy::animation()
{
	switch (_state) {
	case WALK:
		_count++;
		_imageWalk->setFrameY(0);
		if (_count % 20 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >=3)
			{
				_currentFrameX = 0;
				_count = 0;
			}
			_imageWalk->setFrameX(_currentFrameX);
		}
		break;
	case ATTACK1:
		_count++;
		_imageAttack1->setFrameY(0);
		if (_count % 10 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= 5)
			{
				_currentFrameX = 0;
				_count = 0;
			}
			_imageAttack1->setFrameX(_currentFrameX);
		}
		break;
	case ATTACK2:
		_count++;
		_imageAttack2->setFrameY(0);
		if (_count % 10 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= 4)
			{
				_currentFrameX = 0;
				_count = 0;
			}
			_imageAttack2->setFrameX(_currentFrameX);
		}
		break;
	}
}

/*������ �Ⱦ��ϴ�
bool enemy::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireConut == 0)
	{
		_rndFireConut = RANDOM->Range(1, 1000);
		_fireCount = 0;

		return true;
	}
	return false;
}*/
