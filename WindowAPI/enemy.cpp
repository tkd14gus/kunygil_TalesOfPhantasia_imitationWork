#include "stdafx.h"
#include "enemy.h"


//#=====================================================================================#
//#									MUMMY												#											
//#=====================================================================================#



HRESULT mummy::init()
{
	return S_OK;
}

HRESULT mummy::init(POINT position)
{
	//프레임 변수 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//이미지 불러오기(1)
	_imageIdle = IMAGEMANAGER->findImage("mummyidle");
	_imageWalk = IMAGEMANAGER->findImage("mummywalk");
	_imageHit = IMAGEMANAGER->findImage("mummyhit");
	_imageAttack1 = IMAGEMANAGER->findImage("mummyatt1");
	_imageAttack2 = IMAGEMANAGER->findImage("mummyatt2");
	_imageGuard = IMAGEMANAGER->findImage("mummyguard");
	_imageDead = IMAGEMANAGER->findImage("mummydead");
	_hp = 5;
	_attCd = 250;

	//적 개체 생성 위치
	_state = eWALK;
	playerWidth = _imageIdle->getWidth() - 60;
	playerheight = _imageIdle->getHeight()/2 - 20;
	_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight/2);
	_attRcK = RectMakeCenter(_rc.left - 20, playerY, 40, playerheight/2);
	playerX = position.x;
	playerY = position.y - playerheight / 2;

	//#====================================================================================================
	//#				위쪽에 불러온 이미지는 임시입니다
	//#				선택된 적 타입에 따라 다른 이미지를 입힙니다(이미지가 없어서 비워둠)
	//#				위쪽에서 불러온 항목(*이미지 불러오기(1) 항목)은 아래 항목이 수정되면 지웁니다
	//#=====================================================================================================
	/*
	type = rand()c % 3; //적 c타입 랜덤으로 지정하기
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
	_isLeft = true;
	_hitAtt = false;
	collision = false;

	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	return S_OK;
}

void mummy::release()
{
}

void mummy::update(int playerViewX)
{
	if (_fireCount < _attCd) { _fireCount++; }
	_rc = RectMakeCenter(playerX- playerViewX, playerY, playerWidth, playerheight);
	_attRcK = RectMakeCenter(0, 0, 0, 0);



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
	//	//캐릭터 팔이 늘어남에 따라 렉트가 늘어나게 변경하려고 (1)과 같이 설정했는데 위치 오류가 날 것 같아서 일단 뒀습니다 
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
	if (_state == eIDLE) { collision = false; }
	this->animation();
}

void mummy::render()
{
	this->draw();

	char str[32];
	sprintf(str, "%d", _fireCount);
	TextOut(getMemDC(), 100, 550, str, strlen(str));

}

void mummy::move()
{
	//플레이어와 충돌하지 않을 경우 전진
	switch (collision)
	{
	case true:
		if (_fireCount < _attCd)
		{
			_state = eIDLE;
		}

		break;
	case false:
		if (_state == eIDLE && _fireCount > 50)
		{
			_state = eWALK;
		}
		break;
	}

	//상태에 따른 이동값
	switch (_state) {
	case eWALK:
		if (_isLeft) { playerX--; }
		else{ playerX++; }
		break;
	case eHIT:
		if (_isLeft) { playerX+=3; }
		else { playerX-=3; }
		break;
	case eATTACK1:
		if (_currentFrameX > 3)
		{
			if (_isLeft) { _attRcK = RectMakeCenter(_rc.left - 20, playerY, 40, playerheight); }
			else { _attRcK = RectMakeCenter(_rc.right + 30, playerY, 60, playerheight); }
		}
		break;
	case eATTACK2:
		if (_currentFrameX > 2)
		{
			if (_isLeft) { _attRcK = RectMakeCenter(_rc.left, playerY, 40, playerheight); }
			else { _attRcK = RectMakeCenter(_rc.right+10, playerY, 40, playerheight); }
		}
		break;
	}
}

void mummy::draw()
{
	Rectangle(getMemDC(), _rc);
	Rectangle(getMemDC(), _attRcK);
	switch (_state) {
	case eIDLE:
		if (_isLeft) { _imageIdle->frameRender(getMemDC(), _rc.left - playerWidth / 2-10 , _rc.top - 20); }
		else { _imageIdle->frameRender(getMemDC(), _rc.left , _rc.top - 20); }

		//_imageIdle->render(getMemDC(), _rc.left - 95, _rc.top - 20);
		break;
	case eWALK:
		if (_isLeft) { _imageWalk->frameRender(getMemDC(), _rc.left - playerWidth / 2 -10, _rc.top - 20); }
		else{ _imageWalk->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageWalk->frameRender(getMemDC(), _rc.left - 65, _rc.top - 20);
		break;
	case eHIT:
		if (_isLeft) { _imageHit->frameRender(getMemDC(), _rc.left - playerWidth / 2 - 10, _rc.top - 20); }
		else { _imageHit->frameRender(getMemDC(), _rc.left , _rc.top - 20); }
		
		//_imageHit->render(getMemDC(), _rc.left - 75, _rc.top - 20);
		break;
	case eATTACK1:
		if (_isLeft) { _imageAttack1->frameRender(getMemDC(), _rc.left - playerWidth / 2-10, _rc.top - 20); }
		else{ _imageAttack1->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageAttack1->frameRender(getMemDC(), _rc.left - 95, _rc.top - 20);
		break;
	case eATTACK2:
		if (_isLeft) { _imageAttack2->frameRender(getMemDC(), _rc.left - playerWidth / 2-10, _rc.top - 20); }
		else { _imageAttack2->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageAttack2->frameRender(getMemDC(), _rc.left - 50, _rc.top - 5);
		break;
	case eGUARD:
		_imageGuard->frameRender(getMemDC(), _rc.left - playerWidth / 2 - 10, _rc.top - 20);
		//_imageGuard->render(getMemDC(), _rc.left - 60, _rc.top - 20);
		break;
	case eDEAD:
		_imageDead->frameRender(getMemDC(), _rc.left - playerWidth / 2 - 10, _rc.top - 20);
		//_imageDead->render(getMemDC(), _rc.left - 33, _rc.top - 20);
		break;
	}
}

void mummy::animation()
{
	switch (_state) {
	case eIDLE:
		if (_isLeft) { _imageIdle->setFrameY(0); }
		else { _imageIdle->setFrameY(1); }
		break;
	case eWALK:
		_count++;
		if (_isLeft)
		{
			_imageWalk->setFrameY(0);
			if (_count % 20 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 3)
				{
					_currentFrameX = 0;
					_count = 0;
				}
				_imageWalk->setFrameX(_currentFrameX);
			}
		}
		else
		{
			_imageWalk->setFrameY(1);
			if (_count % 20 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 3)
				{
					_currentFrameX = 0;
					_count = 0;
				}
				_imageWalk->setFrameX(_currentFrameX);
			}
		}
		break;
	case eATTACK1:
		_count++;
		if (_isLeft)
		{
			_imageAttack1->setFrameY(0);
			if (_count % 25 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 5)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack1->setFrameX(_currentFrameX);
			}
		}
		else
		{
			{
				_imageAttack1->setFrameY(1);
				if (_count % 25 == 0)
				{
					_currentFrameX++;
					if (_currentFrameX >= 5)
					{
						_hitAtt = false;
						_state = eIDLE;
						_currentFrameX = 0;
						_fireCount = 0;
						_count = 0;
					}
					_imageAttack1->setFrameX(_currentFrameX);
				}
			}
		}
		break;
	case eATTACK2:
		_count++;
		if (_isLeft)
		{
			_imageAttack2->setFrameY(0);
			if (_count % 25 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 4)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack2->setFrameX(_currentFrameX);
			}
		}
		else
		{
			_imageAttack2->setFrameY(1);
			if (_count % 25 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 4)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack2->setFrameX(_currentFrameX);
			}
		}
		break;
	case eHIT:
		_count++;
		if (_isLeft)
		{
			_imageHit->setFrameY(0);
			if (_count > 18) { playerX -= 3; }
			if (_count % 25 == 0)
			{
				_state = eIDLE;
				_fireCount -= 30;
				_count = 0;
			}
		}
		else
		{
			_imageHit->setFrameY(1);
			if (_count > 18) { playerX += 3; }
			if (_count % 25 == 0)
			{
				_state = eIDLE;
				_fireCount -= 30;
				_count = 0;
			}
		}
		break;
	}
}

void mummy::setActionK(int pattern)
{
	STATE state;
	if (pattern == 1) { state = eIDLE; }
	else if (pattern == 2) { state = eWALK; }
	else if (pattern == 3) { state = eHIT; }
	else if (pattern == 4) { state = eATTACK1; }
	else if (pattern == 5) { state = eATTACK2; }
	else if (pattern == 6) { state = eGUARD; }
	else if (pattern == 7) { state = eDEAD; }
	if (_state != state)
	{
		_currentFrameX = 0;
	}
	_state = state;
}

//지금은 안씁니다
bool mummy::bulletCountFire()
{
	//_fireCount++;
	//if (_fireCount % _rndFireConut == 0)
	//{
	//	_rndFireConut = RANDOM->Range(1, 1000);
	//	_fireCount = 0;
	//
	//	return true;
	//}
	//return false;
	return 0;
}



//#=====================================================================================#
//#									GOLEM												#											
//#=====================================================================================#





HRESULT golem::init()
{
	return S_OK;
}

HRESULT golem::init(POINT position)
{
	//프레임 변수 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//이미지 불러오기(1)
	_imageIdle = IMAGEMANAGER->findImage("golemidle");
	_imageWalk = IMAGEMANAGER->findImage("golemwalk");
	_imageHit = IMAGEMANAGER->findImage("golemhit");
	_imageAttack1 = IMAGEMANAGER->findImage("golematt1");
	_imageAttack2 = IMAGEMANAGER->findImage("golematt2");
	_imageGuard = IMAGEMANAGER->findImage("golemguard");

	_hp = 8;
	_attCd = 450;
	//적 개체 생성 위치
	_state = eWALK;
	playerWidth = _imageIdle->getWidth() - 30;
	playerheight = _imageIdle->getHeight()/2 - 20;
	_rc = RectMakeCenter(playerX, playerY, playerWidth, playerheight/2);
	_attRcK = RectMakeCenter(_rc.left - 20, playerY, 40, playerheight/2);
	playerX = position.x;
	playerY = position.y - playerheight / 2;

	_hitAtt = false;
	collision = false;

	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	return S_OK;
}

void golem::release()
{
}

void golem::update(int playerViewX)
{
	if (_fireCount < _attCd) { _fireCount++; }
	_rc = RectMakeCenter(playerX- playerViewX, playerY, playerWidth, playerheight);
	_attRcK = RectMakeCenter(0, 0, 0, 0);


	this->move();
	if (_state == eIDLE) { collision = false; }
	this->animation();
}

void golem::render()
{
	this->draw();

	char str[32];
	sprintf(str, "%d", _count);
	TextOut(getMemDC(), 100, 550, str, strlen(str));
	sprintf(str, "%d", _fireCount);
	TextOut(getMemDC(), 100, 520, str, strlen(str));
}

void golem::move()
{

	//플레이어와 충돌하지 않을 경우 전진
	switch (collision)
	{
	case true:
		if (_fireCount < _attCd)
		{
			_state = eIDLE;
		}
		break;
	case false:
		if (_state == eIDLE && _fireCount > 80)
		{
			_state = eWALK;
		}
		break;
	}

	//상태에 따른 이동값
	switch (_state) {
	case eWALK:
		if (_isLeft) { if (_count % 3 == 0) { playerX--; } }
		else { if (_count % 3 == 0) { playerX++; } }
		break;
	case eHIT:
		if (_isLeft) { playerX += 2; }
		else { playerX -= 2; }
		break;
	case eATTACK1:
		if (_isLeft) { if (_currentFrameX == 1) { _attRcK = RectMakeCenter(_rc.left - 20, playerY, 50, playerheight); } }
		else { if (_currentFrameX == 1) { _attRcK = RectMakeCenter(_rc.right + 10, playerY, 50, playerheight); } }
		break;
	case eATTACK2:
		if (_isLeft) { if (_currentFrameX == 1) { _attRcK = RectMakeCenter(_rc.left, playerY, 40, playerheight); } }
		else  { if (_currentFrameX == 1) { _attRcK = RectMakeCenter(_rc.right-20, playerY, 40, playerheight); } }
		break;
	}
}

void golem::draw()
{
	Rectangle(getMemDC(), _rc);
	Rectangle(getMemDC(), _attRcK);
	switch (_state) {
	case eIDLE:
		if (_isLeft) { _imageIdle->frameRender(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20); }
		else{ _imageIdle->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageIdle->render(getMemDC(), _rc.left - 95, _rc.top - 20);
		break;
	case eWALK:
		if (_isLeft) { _imageWalk->frameRender(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20); }
		else { _imageWalk->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageWalk->frameRender(getMemDC(), _rc.left - 65, _rc.top - 20);
		break;
	case eHIT:
		if (_isLeft) { _imageHit->frameRender(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20); }
		else { _imageHit->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageHit->render(getMemDC(), _rc.left - 75, _rc.top - 20);
		break;
	case eATTACK1:
		if (_isLeft) { _imageAttack1->frameRender(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20); }
		else { _imageAttack1->frameRender(getMemDC(), _rc.left , _rc.top - 20); }
		//_imageAttack1->frameRender(getMemDC(), _rc.left - 95, _rc.top - 20);
		break;
	case eATTACK2:
		if (_isLeft) { _imageAttack2->frameRender(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20); }
		else { _imageAttack2->frameRender(getMemDC(), _rc.left, _rc.top - 20); }
		//_imageAttack2->frameRender(getMemDC(), _rc.left - 50, _rc.top - 5);
		break;
	case eGUARD:
		if (_isLeft) { _imageGuard->frameRender(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20); }
		else { _imageGuard->frameRender(getMemDC(), _rc.left , _rc.top - 20); }
		//_imageGuard->render(getMemDC(), _rc.left - 60, _rc.top - 20);
		break;
	//case eDEAD:
	//	_imageDead->render(getMemDC(), _rc.left - playerWidth / 2 + 20, _rc.top - 20);
	//	//_imageDead->render(getMemDC(), _rc.left - 33, _rc.top - 20);
	//	break;
	}
}

void golem::animation()
{
	switch (_state) {
	case eIDLE:
		if (_isLeft) { _imageIdle->setFrameY(0); }
		else { _imageIdle->setFrameY(1); }

		break;
	case eWALK:
		_count++;
		if (_isLeft)
		{
			_imageWalk->setFrameY(0);
			if (_count % 20 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 3)
				{
					_currentFrameX = 0;
					_count = 0;
				}
				_imageWalk->setFrameX(_currentFrameX);
			}
		}
		else
		{
			{
				_imageWalk->setFrameY(1);
				if (_count % 20 == 0)
				{
					_currentFrameX++;
					if (_currentFrameX >= 3)
					{
						_currentFrameX = 0;
						_count = 0;
					}
					_imageWalk->setFrameX(_currentFrameX);
				}
			}
		}
		break;
	case eATTACK1:
		_count++;
		if (_isLeft)
		{
			_imageAttack1->setFrameY(0);

			if (_count % 60 == 0 || _count > 100)
			{
				_currentFrameX++;
				if (_currentFrameX >= 3)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack1->setFrameX(_currentFrameX);
			}
		}
		else
		{
			_imageAttack1->setFrameY(1);

			if (_count % 60 == 0 || _count > 100)
			{
				_currentFrameX++;
				if (_currentFrameX >= 3)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack1->setFrameX(_currentFrameX);
			}
		}
		break;
	case eATTACK2:
		_count++;
		if (_isLeft)
		{
			_imageAttack2->setFrameY(0);
			if (_count % 60 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 2)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack2->setFrameX(_currentFrameX);
			}
		}
		else
		{
			_imageAttack2->setFrameY(1);
			if (_count % 60 == 0)
			{
				_currentFrameX++;
				if (_currentFrameX >= 2)
				{
					_hitAtt = false;
					_state = eIDLE;
					_currentFrameX = 0;
					_fireCount = 0;
					_count = 0;
				}
				_imageAttack2->setFrameX(_currentFrameX);
			}
		}
		break;
	case eHIT:
		_count++;
		if (_isLeft)
		{
			_imageHit->setFrameY(0);
			if (_count > 18) { playerX -= 3; }
			if (_count % 25 == 0)
			{
				_state = eIDLE;
				_fireCount -= 10;
				_count = 0;
			}
		}
		else
		{
			{
				_imageHit->setFrameY(1);
				if (_count > 18) { playerX += 3; }
				if (_count % 25 == 0)
				{
					_state = eIDLE;
					_fireCount -= 10;
					_count = 0;
				}
			}
		}
		break;
	}
}

bool golem::bulletCountFire()
{
	return false;
}

void golem::setActionK(int pattern)
{
	STATE state;
	if (pattern == 1) { state = eIDLE; }
	else if (pattern == 2) { state = eWALK; }
	else if (pattern == 3) { state = eHIT; }
	else if (pattern == 4) { state = eATTACK1; }
	else if (pattern == 5) { state = eATTACK2; }
	else if (pattern == 6) { state = eGUARD; }
	else if (pattern == 7) { state = eDEAD; }
	if (_state != state)
	{
		_currentFrameX = 0;

	}
	_state = state;
}
