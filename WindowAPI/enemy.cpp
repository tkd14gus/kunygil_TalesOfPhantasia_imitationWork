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
	_imageIdle = IMAGEMANAGER->findImage("mummyidle");
	_imageWalk = IMAGEMANAGER->findImage("mummywalk");
	_imageHit = IMAGEMANAGER->findImage("mummyhit");
	_imageAttack1 = IMAGEMANAGER->findImage("mummyatt1");
	_imageAttack2 = IMAGEMANAGER->findImage("mummyatt2");
	_imageGuard = IMAGEMANAGER->findImage("mummyguard");
	_imageDead = IMAGEMANAGER->findImage("mummydead");

	
	//�� ��ü ���� ��ġ
	_state =eWALK;
	playerWidth = _imageIdle->getWidth()-60;
	playerheight = _imageIdle->getHeight() - 20;
	_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	
	playerX = position.x;
	playerY = position.y -playerheight/2;

	//#====================================================================================================
	//#				���ʿ� �ҷ��� �̹����� �ӽ��Դϴ�
	//#				���õ� �� Ÿ�Կ� ���� �ٸ� �̹����� �����ϴ�(�̹����� ��� �����)
	//#				���ʿ��� �ҷ��� �׸�(*�̹��� �ҷ�����(1) �׸�)�� �Ʒ� �׸��� �����Ǹ� ����ϴ�
	//#=====================================================================================================
	/*
	type = rand()c % 3; //�� cŸ�� �������� �����ϱ�
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
	if (_fireCount < 250) { _fireCount++; }
	_rc = RectMakeCenter(playerX , playerY, playerWidth, playerheight);


	
	//switch (_state) {
	//case eIDLE:
	//	//playerWidth = _imageIdle->getWidth() - 105;
	//	//playerheight = _imageIdle->getHeight() - 20;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//case eWALK:
	//	//playerWidth = _imageIdle->getWidth() - 70;
	//	//playerheight = _imageIdle->getHeight() - 20;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//case eHIT:
	//	//playerWidth = _imageIdle->getWidth() - 75;
	//	//playerheight = _imageIdle->getHeight() - 20;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//case eATTACK1:
	//	//ĳ���� ���� �þ�� ���� ��Ʈ�� �þ�� �����Ϸ��� (1)�� ���� �����ߴµ� ��ġ ������ �� �� ���Ƽ� �ϴ� �׽��ϴ� 
	//	//(1) playerWidth ++;
	//	//playerWidth = _imageIdle->getWidth() - 40;
	//	//playerheight = _imageIdle->getHeight() - 20;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//case eATTACK2:
	//	//playerWidth = _imageIdle->getWidth() - 40;
	//	//playerheight = _imageIdle->getHeight()-5;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//case eGUARD:
	//	//playerWidth = _imageIdle->getWidth() - 70;
	//	//playerheight = _imageIdle->getHeight() - 20;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//case eDEAD:
	//	//playerWidth = _imageIdle->getWidth() - 50;
	//	//playerheight = _imageIdle->getHeight() - 20;
	//	//_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight);
	//	break;
	//}

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
		if (_fireCount < 250)
		{
			_state = eIDLE;
		}

		break;
	case false:
		if (_currentFrameX == 0&& _state == eIDLE)
		{
			_state = eWALK;
		}
		break;
	}

	//���¿� ���� �̵���
	switch (_state) {
	case eWALK:
		playerX--;
		break;
	case eHIT:
		break;
	case eATTACK1:
		break;
	case eATTACK2:
		break;
	}
}

void enemy::draw()
{
	Rectangle(getMemDC(), _rc);
	switch (_state) {
	case eIDLE:
		_imageIdle->render(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageIdle->render(getMemDC(), _rc.left - 95, _rc.top - 20);
		break;
	case eWALK:
		_imageWalk->frameRender(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageWalk->frameRender(getMemDC(), _rc.left - 65, _rc.top - 20);
		break;
	case eHIT:
		_imageHit->render(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageHit->render(getMemDC(), _rc.left - 75, _rc.top - 20);
		break;
	case eATTACK1:
		_imageAttack1->frameRender(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageAttack1->frameRender(getMemDC(), _rc.left - 95, _rc.top - 20);
		break;
	case eATTACK2:
		_imageAttack2->frameRender(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageAttack2->frameRender(getMemDC(), _rc.left - 50, _rc.top - 5);
		break;
	case eGUARD:
		_imageGuard->render(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageGuard->render(getMemDC(), _rc.left - 60, _rc.top - 20);
		break;
	case eDEAD:
		_imageDead->render(getMemDC(), _rc.left - playerWidth / 2, _rc.top - 20);
		//_imageDead->render(getMemDC(), _rc.left - 33, _rc.top - 20);
		break;
	}	
}

void enemy::animation()
{
	switch (_state) {
	case eWALK:
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
	case eATTACK1:
		_count++;
		_imageAttack1->setFrameY(0);
		if (_count % 25 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= 5)
			{
				_state = eIDLE;
				_currentFrameX = 0;
				_fireCount = 0;
				_count = 0;
			}
			_imageAttack1->setFrameX(_currentFrameX);
		}
		break;
	case eATTACK2:
		_count++;
		_imageAttack2->setFrameY(0);
		if (_count % 25 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= 4)
			{
				_state = eIDLE;
				_currentFrameX = 0;
				_fireCount = 0;
				_count = 0;
			}
			_imageAttack2->setFrameX(_currentFrameX);
		}
		break;
	}
}

void enemy::setActionK(int pattern)
{
	STATE state;
	if (pattern == 1) { state = eIDLE; }
	if (pattern == 2) { state = eWALK; }
	if (pattern == 3) { state = eHIT; }
	if (pattern == 4) { state = eATTACK1; }
	if (pattern == 5) { state = eATTACK2; }
	if (pattern == 6) { state = eGUARD; }
	if (pattern == 7) { state = eDEAD; }
	if (_state != state)
	{
		_currentFrameX = 0;
	}
	_state = state;
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
