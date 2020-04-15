#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	// �÷��̾� ����ü�� init��Ű�� �ʱ�ȭ �����ش�.
	this->settingTagPlayer();

	//_stage = RectMake(0, 500, WINSIZEX, 300);

	//�������̹����ʱ�ȭ
	_frameCount = 0;
	_frameIndex = 0;
	_player.viewX = 0;
	//�����ð� �ʱ�ȭ
	//_immoTime = 0;

	//_enemyHP = 3;


	//_enemyX = 500;
	//_enemyY = 400;

	// ������ ������ �� �������� �ƴϴ�.
	_isBattle = true;
	// �÷��̾�� ���� ���� ������ �� �Ʒ��� �ٶ󺸰� �ִ�.
	_direct = 1;
	_player.cameraRc = RectMakeCenter(_player.x, _player.y, 300, 200);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (_isBattle)
	{
		//�ǽð� �÷��̾� ��ġ �� �ӵ�
		_player.rc = RectMakeCenter(_player.x, _player.y, 75, 80);
		_player.cameraRc = RectMakeCenter(_player.x, _player.y, 300, 200);
	
		if (!(_player._state == pATTACK || _player._state == pJUMP))
		{
			_player.attXK = 0;
			_player.attYK = 0;
		}
		if (_player.sight == true)	//�÷��̾ �������� �ٶ󺸰� ���� ��
		{
			_player.attack = RectMake(_player.rc.right - 20, _player.rc.top, _player.attXK, _player.attYK);
			//_player.jumpAttack = RectMake(_rcPlayer.right - 20, _rcPlayer.top, 50, 160);
		}
		else if (_player.sight == false)  //�÷��̾ ������ �ٶ󺸰� ���� ��
		{
			_player.attack = RectMake(_player.rc.left - 20, _player.rc.top, _player.attXK, _player.attYK);
			//_player.jumpAttack = RectMake(_rcPlayer.left - 20, _rcPlayer.top, 50, 160);
		}
		//���ݿ� ��Ʈ
		if (_player._state == pWALK)
		{
			_player.speed = 3.0f;
		}
		else if (_player._state == pRUN)
		{
			_player.speed = 5.0f;
		}

		//�ǽð� ���� ��ġ
		//_TESTenemy = RectMake(_enemyX, _enemyY, 50, 50);

		//���簢�� ����
		//_enemyCenterX = _enemyX + float((_TESTenemy.right - _TESTenemy.left) / 2);
		//_enemyCenterY = _enemyY + float((_TESTenemy.bottom - _TESTenemy.top) / 2);

		//test - HP down
		if (INPUT->GetKeyDown('Q'))
		{
			_player.hp--;
			if (_player.hp <= 0)
			{
				_frameIndex = 0;
			}
		}
		if (INPUT->GetKeyDown('W'))
		{
			_player.hp++;
			_player._state = pIDLE;
		}
		if (INPUT->GetKeyDown('E'))
		{
			_player.gravity = 3.f;
			_player._state = pHIT;
			_frameIndex = 0;
			_frameCount = 0;
		}
		//�׼��׽�Ʈ

		//sight left & walk left
		if (INPUT->GetKey(VK_LEFT))
		{
			if (_player._state == pATTACK)
			{
				_player._state = pATTACK;
			}
			else if (_player._state == pGUARD)
			{
				_player.sight = 0;
				_player._state = pGUARD;
			}
			else if (_player._state == pJUMP)
			{
				_player._state = pJUMP;
				if (_player.viewX == 0 && _player.x > 37) { _player.x -= 3; }
				else if (_player.cameraRc.left < 0) { _player.viewX -= 3; }
				else { _player.x -= 3; }
			}
			else if (_player._state == pHIT)
			{
				_player._state = pHIT;
			}
			else if (_player._state == pWIN)
			{
				_player._state = pWIN;
			}
			else if (_player._state == pDEAD)
			{
				_player._state = pDEAD;
				if (_frameIndex >= 2)
				{
					_player.sight = 0;					 //�÷��̾� ���� - ����
					if (_player.viewX == 0 && _player.x > 37) { _player.x -= _player.speed; }
					else if (_player.cameraRc.left < 0) { _player.viewX -= _player.speed; }
					else { _player.x -= _player.speed; }	  //�÷��̾� ��ǥ ��ȭ
				}
			}
			else
			{
				if (INPUT->GetKey(VK_SHIFT))
				{
					_player.sight = 0;				 //�÷��̾� ���� - ����
					_player._state = pRUN;			 //�÷��̾� ���� - �ٱ�
					if (_player.viewX == 0 && _player.x > 37) { _player.x -= _player.speed; }
					else if (_player.cameraRc.left < 0) { _player.viewX -= _player.speed; }
					else { _player.x -= _player.speed; }    //�÷��̾� ��ǥ ��ȭ
				}
				else
				{
					_player.sight = 0;				 //�÷��̾� ���� - ����
					_player._state = pWALK;			 //�÷��̾� ���� - �ȱ�
					if (_player.viewX ==0  && _player.x > 37) { _player.x -= _player.speed; }
					else if (_player.cameraRc.left < 0) { _player.viewX -= _player.speed; }
					else { _player.x -= _player.speed; }      //�÷��̾� ��ǥ ��ȭ
				}
			}
		}
		//state idle
		if (INPUT->GetKeyUp(VK_LEFT) && _player._state != pATTACK 
			&& _player._state != pWIN && _player._state != pDEAD)
		{
			if (_player._state != pGUARD)
			{
				if (_player._state != pHIT)
				{
					_player._state = pIDLE;
				}
			}
		}
		//sight right & walk right
		if (INPUT->GetKey(VK_RIGHT))
		{
			if (_player._state == pATTACK)
			{
				_player._state = pATTACK;
			}
			else if (_player._state == pGUARD)
			{
				_player.sight = 1;
				_player._state = pGUARD;
			}
			else if (_player._state == pJUMP)
			{
				_player._state = pJUMP;
				if (_player.viewX == 900 && _player.x < WINSIZEX-37) { _player.x += _player.speed; }
				else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += 3; }
				else { _player.x += 3; }
			}
			else if (_player._state == pHIT)
			{
				_player._state = pHIT;
			}
			else if (_player._state == pWIN)
			{
				_player._state = pWIN;
			}
			else if (_player._state == pDEAD)
			{
				_player._state = pDEAD;
				if (_frameIndex >= 2)
				{
					_player.sight = 1;				 //�÷��̾� ���� - ����
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x += _player.speed; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += _player.speed; }
					else { _player.x += _player.speed; }                //�÷��̾� ��ǥ ��ȭ
				}
			}
			else
			{
				if (INPUT->GetKey(VK_SHIFT))
				{
					
					_player.sight = 1;				 //�÷��̾� ���� - ������
					_player._state = pRUN;			         //�÷��̾� ���� - �ٱ�
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x += _player.speed; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += _player.speed; }
					else { _player.x += _player.speed; }                 //�÷��̾� ��ǥ ��ȭ
				}
				else
				{
					_player.sight = 1;				 //�÷��̾� ���� - ������
					_player._state = pWALK;			         //�÷��̾� ���� - �ȱ�
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x += _player.speed; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += _player.speed; }
					else { _player.x += _player.speed; }                  //�÷��̾� ��ǥ ��ȭ
				}
			}
		}
		//state idle
		if (INPUT->GetKeyUp(VK_RIGHT) && _player._state != pATTACK  
			&& _player._state != pWIN && _player._state != pDEAD)
		{

			if (_player._state != pGUARD)
			{
				if (_player._state != pHIT)
				{
					_player._state = pIDLE;
				}
			}
		}


		//test - state attack -> ����� ���, �����ÿ��� ���� ���� �������� �߰�����
		if (INPUT->GetKeyDown('Z') && _player._state != pDEAD && _player._state != pJUMP && _player._state != pHIT && _player._state != pWIN && _player._state != pDEAD && _player._state != pATTACK)
		{
			_player._state = pATTACK;
			if (_player._state != pATTACK)
			{
				_frameIndex = 0;
			}

			_player.attXK = 50;
			_player.attYK = 130;

		}

		//test - state guard
		if (INPUT->GetKey('X') && _player._state != pJUMP && _player._state != pHIT 
			&& _player._state != pWIN && _player._state != pDEAD)
		{
			_player._state = pGUARD;
		}
		if (INPUT->GetKeyUp('X') && _player._state != pHIT && _player._state != pWIN && _player._state != pDEAD)
		{
			_player._state = pIDLE;
		}

		// state jump
		if (INPUT->GetKeyDown('C') && _player._state != pJUMP && _player._state != pWIN && _player._state != pDEAD)
		{
			if (_player._state != pHIT)
			{
				_frameIndex = 0;
				_player._state = pJUMP;
				_player.gravity = 0.0f;
				_player.attXK = 50;
				_player.attYK = 130;
			}
		}

		if (_player._state == pJUMP || _player._state == pHIT)
		{
			_player.x += cosf(PI / 2) * 1;
			_player.y += -sinf(PI / 2) * 5 + _player.gravity;
			_player.gravity += 0.1f;
		}



		//test - state win
		if (INPUT->GetKeyDown(VK_F5))
		{
			_frameIndex = 0;
			_frameCount = 0;
			_player._state = pWIN;
		}

		//�ٴڿ� ��� �Ǿ�����
		if (_player.y > 460 && _player._state == pJUMP)
		{
			_player.gravity = 0.0f;
			_player._state = pIDLE;
			_player.y = 460;
		}
		if (_player.y > 470 && _player._state == pHIT)
		{

			_player.y = 470;
		}
		//���߿��� �ٸ� ����� ������� �ʵ��� ����
		if (_player.y < 460 && _player._state != pJUMP)
		{
			if (_player._state != pHIT)
			{
				_player._state = pJUMP;
			}
		}
		if (_player.y < 460 && _player._state != pHIT)
		{
			if (_player._state != pJUMP)
			{
				_player._state = pHIT;
			}
		}
		//�÷��̾� ���
		if (_player.hp <= 0)
		{
			if (_player._state != pDEAD)
			{
				_frameCount = 0;
				IMAGEMANAGER->findImage("dead")->setFrameX(0);
			}
			_player._state = pDEAD;
			_player.rc = RectMakeCenter(_player.x - 75 / 2, _player.y - 80 / 2, 0, 0);

			if (_frameCount > 200)
			{
				SCENEMANAGER->loadScene("����ȭ��");
			}
		}
		if (_player._state == pWIN)
		{
			_player._state = pWIN;
		}

		if (_player.viewX < 0) { _player.viewX = 0; }
		else if (_player.viewX > 900) { _player.viewX = 900; }

		//RECT temp;
		////���� Ÿ�ݹ����� ������ �浹
		//if (IntersectRect(&temp, &_player.attack, &_TESTenemy))
		//{
		//	_player.attXK = 0;
		//	_player.attYK = 0;
		//	_enemyHP -= 1;
		//}
	}
	else
	{
	// ����Ű�� ������ ��
	if (INPUT->GetKey(VK_UP))
	{
		//�����̸� ���� ���¸� walk�� �ٲ��ش�.
		_player._state = pWALK;
		//�����̴� ������ �������ش�.
		//�����̹Ƿ� 0.
		_direct = 0;
		//�������� �����̹Ƿ� Y��ǥ�� --�����ش�.
		_player.inGameY--;
	}
	// ����Ű�� ���� ��
	if (INPUT->GetKeyUp(VK_UP))
	{
		//�������� idle�� �ٲ��ش�.
		_player._state = pIDLE;
	}
	// �Ʒ���Ű�� ������ ��
	if (INPUT->GetKey(VK_DOWN))
	{
		//�����̸� ���� ���¸� walk�� �ٲ��ش�.
		_player._state = pWALK;
		//�����̴� ������ �������ش�.
		//�����̹Ƿ� 1
		_direct = 1;
		//�������� �����̹Ƿ� Y��ǥ�� ++�����ش�.
		_player.inGameY++;
	}
	// �Ʒ���Ű�� ���� ��
	if (INPUT->GetKeyUp(VK_DOWN))
	{
		//�������� idle�� �ٲ��ش�.
		_player._state = pIDLE;
	}
	// ����Ű�� ������ ��
	if (INPUT->GetKey(VK_LEFT))
	{
		//�����̸� ���� ���¸� walk�� �ٲ��ش�.
		_player._state = pWALK;
		//�����̴� ������ �������ش�.
		//�����̹Ƿ� 2.
		_direct = 2;
		//�������� �����̹Ƿ� X��ǥ�� --�����ش�.
		_player.inGameX--;
	}
	// ����Ű�� ���� ��
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		//�������� idle�� �ٲ��ش�.
		_player._state = pIDLE;
	}
	// ������Ű�� ������ ��
	if (INPUT->GetKey(VK_RIGHT))
	{
		//�����̸� ���� ���¸� walk�� �ٲ��ش�.
		_player._state = pWALK;
		//�����̴� ������ �������ش�.
		//�����̹Ƿ� 3.
		_direct = 3;
		//�������� �����̹Ƿ� X��ǥ�� ++�����ش�.
		_player.inGameX++;
	}
	// ������Ű�� ���� ��
	if (INPUT->GetKeyUp(VK_RIGHT))
	{
		//�������� idle�� �ٲ��ش�.
		_player._state = pIDLE;
	}

	// �÷��̾��� ��ġ�� ��� �ʱ�ȭ �Ѵ�.
	_player.rc = RectMakeCenter(_player.inGameX, _player.inGameY, 64, 128);
	// �÷��̾��� �� �浹�� ��Ʈ ��ġ�� ��� �ʱ�ȭ �Ѵ�.
	this->settingPlayerDoorRect();
	//_playerDoorRcP = RectMakeCenter(_player.inGameX, _player.inGameY, 64 + 48 * 2, 128 + 48 * 2);

	}

	_frameCount++;

}

void player::render()
{
	//��Ʋ�� ��
	if (_isBattle)
	{
				
		//Rectangle(getMemDC(), _stage);

		Rectangle(getMemDC(), _player.rc);		//�÷��̾� Ÿ�ݹ��� �簢��

		Rectangle(getMemDC(), _player.attack);		//�÷��̾� Ÿ�ݹ��� �簢��

		FrameRect(getMemDC(), _player.cameraRc, RGB(140, 60, 180));

		this->animation();					//�÷��̾� ��� �ִϸ��̼�
											//��Ʋ�� �� �ִϸ��̼����� �����ϴϱ� �ڿ� �д�.

		SetTextColor(getMemDC(), RGB(255, 255, 255));

		char chr1[100];
		sprintf_s(chr1, "player hp : %d", _frameCount);
		TextOut(getMemDC(), 100, 720, chr1, strlen(chr1));

		sprintf_s(chr1, "player hp : %d", _player.hp);
		TextOut(getMemDC(), 100, 680, chr1, strlen(chr1));
		SetTextColor(getMemDC(), RGB(0, 0, 0));

	}
	else
	{
		this->animation();					//�÷��̾� ��� �ִϸ��̼�
											//��Ʋ�� �ƴҶ� ������X, Y���� �ٲ��ֱ� ������ ���� ���� �Լ��� �ҷ��ش�.

		//�� �浹�� ���� ��Ʈ �����ֱ�
		FrameRect(getMemDC(), _playerDoorRc, RGB(255, 0, 0));

		// �÷��̾ �ȴ� ���¶��
		if (_player._state == pWALK)
		{
			//���� �÷��̾��� x���� WINSIZEX / 2���� ũ��, (48 * 120 - WINSIZEX / 2)���� ������(x���� ����� ��)
			if (_player.inGameX >= WINSIZEX / 2 && _player.inGameX <= (48 * 120 - WINSIZEX / 2))
			{
				//���� y���� ������
				if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
				{
					//��Ʈ�� �� �߽ɿ� �׸��� ���� �ƴ϶� left, top�� ��ǥ�̹Ƿ� ���� ũ�⸸ŭ ���ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, WINSIZEY / 2 - 64);
				}
				//y���� ���ʿ� ġ������ �ִٸ�
				else if (_player.inGameY < WINSIZEY / 2)
				{
					//x�� �߽ɰ�, y�� ĳ������ top���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top);
				}
				//y���� �Ʒ��ʿ� ġ������ �ִٸ�
				else
				{
					//x�� �߽ɰ�, y�� (48 * 150 - WINSIZEY)������ �÷��̾� top���� �� ���� �ش�.
					//_player.rc.top - (48 * 150 - WINSIZEY)�� ������ �÷��̾��� ��ġ�� WINSIZEY�ȿ� �׷���� �ϴµ�
					//y��ǥ�� �̹�  WINSIZEY�� �ʰ��� �����̴�.
					//������ ���� ��ǥ���� ��ü �� ũ���� 48 * 150�� ȭ�� Y�� ũ���� WINSIZEY�� �� ����
					//�÷��̾� ��ǥ���� ���ָ� ȭ�鿡 ���̸鼭  WINSIZEY �ȿ��� �÷��̾ ������ �� �ִ�.
					//���ķ� ������ Y��ǥ�� X��ǥ ��� ���� �����̴�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top - (48 * 150 - WINSIZEY));
				}

			}
			//���� �÷��̾��� y���� WINSIZEY / 2���� ũ��, (48 * 150 - WINSIZEY / 2)���� ���� ��(y���� ����� ��)
			else if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
			{
				//���� x���� �����̶��
				if (_player.inGameX < WINSIZEX / 2)
				{
					//�÷��̾��� x���� �÷��̾��� ����, y���� �߽ɰ��� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, WINSIZEY / 2 - 64);
				}
				//���� x���� �������̶��
				else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
				{
					//�÷��̾��� x���� _player.rc.left - (48 * 120 - WINSIZEX)���� , y���� �߽ɰ��� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), WINSIZEY / 2 - 64);
				}
			}
			//�÷��̾� x�� ���ʿ� ġ������ ���� ��
			else if (_player.inGameX < WINSIZEX / 2)
			{
				//���� y�� ���ʿ� ġ������ �ִٸ�
				if (_player.inGameY < WINSIZEY / 2)
				{
					//x�÷��̾��� ���� x��, y�� ĳ������ top���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top);
				}
				//y���� �Ʒ��ʿ� ġ������ �ִٸ�
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//x�÷��̾��� ���� x��, y�� ĳ������  _player.rc.top - (48 * 150 - WINSIZEY)���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top - (48 * 150 - WINSIZEY));
				}
			}
			//�÷��̾� x�� �����ʿ� ġ������ ���� ��
			else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
			{
				//���� y�� ���ʿ� ġ������ �ִٸ�
				if (_player.inGameY < WINSIZEY / 2)
				{
					//�÷��̾�x��  _player.rc.left - (48 * 120 - WINSIZEX)��, y�� ĳ������ top���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top);
				}
				//y���� �Ʒ��ʿ� ġ������ �ִٸ�
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//�÷��̾���x�� _player.rc.left - (48 * 120 - WINSIZEX)��, y�� ĳ������  _player.rc.top - (48 * 150 - WINSIZEY)���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top - (48 * 150 - WINSIZEY));
				}
			}
		}
		// �÷��̾ �����ִ� ���¶�� currentX��ǥ�� �׻� 2������ �����ִ�.
		// ������ walk�϶��� �ٸ��� �ڿ� 2,  _directP); �� �߰��� �����ش�.
		else
		{
			//���� �÷��̾��� x���� WINSIZEX / 2���� ũ��, (48 * 120 - WINSIZEX)���� ������(x���� ����� ��)
			if (_player.inGameX >= WINSIZEX / 2 && _player.inGameX <= (48 * 120 - WINSIZEX / 2))
			{
				//���� y���� ������
				if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
				{
					//��Ʈ�� �� �߽ɿ� �׸��� ���� �ƴ϶� left, top�� ��ǥ�̹Ƿ� ���� ũ�⸸ŭ ���ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, WINSIZEY / 2 - 64, 2, _direct);
				}
				//y���� ���ʿ� ġ������ �ִٸ�
				else if (_player.inGameY < WINSIZEY / 2)
				{
					//x�� �߽ɰ�, y�� ĳ������ top���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top, 2, _direct);
				}
				//y���� �Ʒ��ʿ� ġ������ �ִٸ�
				else
				{
					//�÷��̾���x�� �߽ɿ��� ������ ���ݸ�ŭ �� WINSIZEX / 2 - 32�� �ְ�,, y�� ĳ������  _player.rc.top - (48 * 150 - WINSIZEY)���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top - (48 * 150 - WINSIZEY), 2, _direct);
				}

			}
			//���� �÷��̾��� y���� WINSIZEY / 2���� ũ��, (48 * 150 - WINSIZEY / 2)���� ���� ��(y���� ����� ��)
			else if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
			{
				//���� x���� �����̶��
				if (_player.inGameX < WINSIZEX / 2)
				{
					//�÷��̾��� x���� �÷��̾��� ����, y���� �߽ɰ��� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, WINSIZEY / 2 - 64, 2, _direct);
				}
				//���� x���� �������̶��
				else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
				{
					//�÷��̾��� x���� _player.rc.left - (48 * 120 - WINSIZEX / 2)���� , y���� �߽ɰ��� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), WINSIZEY / 2 - 64, 2, _direct);
				}
			}
			//�÷��̾� x�� ���ʿ� ġ������ ���� ��
			else if (_player.inGameX < WINSIZEX / 2)
			{
				//���� y�� ���ʿ� ġ������ �ִٸ�
				if (_player.inGameY < WINSIZEY / 2)
				{
					//x�÷��̾��� ���� x��, y�� ĳ������ top���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top, 2, _direct);
				}
				//y���� �Ʒ��ʿ� ġ������ �ִٸ�
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//x�÷��̾��� ���� x��, y�� ĳ������  _player.rc.top - (48 * 150 - WINSIZEY / 2)���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top - (48 * 150 - WINSIZEY), 2, _direct);
				}
			}
			//�÷��̾� x�� �����ʿ� ġ������ ���� ��
			else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
			{
				//���� y�� ���ʿ� ġ������ �ִٸ�
				if (_player.inGameY < WINSIZEY / 2)
				{
					//�÷��̾�x��  _player.rc.left - (48 * 120 - WINSIZEX / 2)��, y�� ĳ������ top���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top, 2, _direct);
				}
				//y���� �Ʒ��ʿ� ġ������ �ִٸ�
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//�÷��̾���x�� _player.rc.left - (48 * 120 - WINSIZEX / 2)��, y�� ĳ������  _player.rc.top - (48 * 150 - WINSIZEY / 2)���� �ش�.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top - (48 * 150 - WINSIZEY), 2, _direct);
				}
			}
		}

	}
}

void player::animation()
{
	//��Ʋ�� ��
	if (_isBattle)
	{
		switch (_player._state)
		{
		case pIDLE:		//������
			//��
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("mIdle", getMemDC(), _player.rc.left, _player.rc.top + 3);
				//_frameCount++;
				_player.idle->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 0;
					}
					_player.idle->setFrameX(_frameIndex);
				}
			}
			//��
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("mIdle", getMemDC(), _player.rc.left, _player.rc.top + 3);
				//_frameCount++;
				_player.idle->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.idle->setFrameX(_frameIndex);
				}
			}
			break;
		case pWALK:		//�ȱ�
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("walk", getMemDC(), _player.rc.left - 10, _player.rc.top + 2);
				//_frameCount++;
				_player.walk->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.walk->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("walk", getMemDC(), _player.rc.left + 10, _player.rc.top + 2);
				//_frameCount++;
				_player.walk->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.walk->setFrameX(_frameIndex);
				}
			}
			break;
		case pRUN:		//�޸���
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("run", getMemDC(), _player.rc.left - 10, _player.rc.top - 5);
				//_frameCount++;
				_player.run->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.run->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("run", getMemDC(), _player.rc.left, _player.rc.top - 5);
				//_frameCount++;
				_player.run->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.run->setFrameX(_frameIndex);
				}
			}
			break;
		case pATTACK:	//������ �ѹ������� �ٽ� �����·� ���� ����
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("slash", getMemDC(), _player.rc.left - 15, _player.rc.top - 10);
				//_frameCount++;
				_player.atkSlash->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("slash")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameCount = 0;
						_frameIndex = 0;
						_player._state = pIDLE;	//�ѹ������� ���´���ڼ���
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("slash", getMemDC(), _player.rc.left - 10, _player.rc.top - 10);
				//_frameCount++;
				_player.atkSlash->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("slash")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
						_player._state = pIDLE;
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			break;
		case pJUMP:
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("jump", getMemDC(), _player.rc.left, _player.rc.top - 20);
				//_frameCount++;
				_player.jump->setFrameY(1);
				if (_frameCount % 15 == 0)
				{
					IMAGEMANAGER->findImage("jump")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameCount = 0;
						_frameIndex = 3;
					}
					_player.jump->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("jump", getMemDC(), _player.rc.left, _player.rc.top - 20);
				//_frameCount++;
				_player.jump->setFrameY(0);
				if (_frameCount % 15 == 0)
				{
					IMAGEMANAGER->findImage("jump")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameCount = 0;
						_frameIndex = 3;
					}
					_player.jump->setFrameX(_frameIndex);
				}
			}
			break;
		case pGUARD:		//����
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("guard", getMemDC(), _player.rc.left, _player.rc.top);
				//_frameCount++;
				_player.guard->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("guard")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 1)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.guard->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("guard", getMemDC(), _player.rc.left, _player.rc.top);
				//_frameCount++;
				_player.guard->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("guard")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 1)
					{
					}
					_player.guard->setFrameX(_frameIndex);
				}
			}
			break;
		case pDEAD:		//����ÿ��� hp = 0�̵Ǿ� ����ϸ� ���ɻ��� ���� - ���� ����۵� ���� ����
			if (_player.sight == false)
			{
				if (_frameIndex >= 2) { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top + 18); }
				//_frameCount++;
				_player.dead->setFrameY(0);
				if (_frameCount % 30 == 0)
				{
					IMAGEMANAGER->findImage("dead")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameIndex = 2;
					}
					_player.dead->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				if (_frameIndex >= 2) { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left + 20, _player.rc.top + 18); }
				//_frameCount++;
				_player.dead->setFrameY(1);
				if (_frameCount % 30 == 0)
				{
					IMAGEMANAGER->findImage("dead")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameIndex = 2;
					}
					_player.dead->setFrameX(_frameIndex);
				}
			}
			break;
		case pWIN:
			IMAGEMANAGER->frameRender("win", getMemDC(), _player.rc.left - 20, _player.rc.top - 54);
			//_frameCount++;
			_player.win->setFrameY(0);
			if (_frameCount % 20 == 0)
			{
				IMAGEMANAGER->findImage("win")->setFrameY(0);
				_frameIndex++;
				_player.win->setFrameX(_frameIndex);
				if (_frameIndex == 7)
				{
					_isBattle = false;
					_player.viewX = 0;
					_player.x = 200;
					_player.y = 460;
					//SCENEMANAGER->loadScene("����ȭ��");
				}
			}
			break;
		case pHIT:		//��Ʈ�� ���ư��� ���� ������ �ö󰡴¼ӵ� / �ε���0,1��ġ���� �� ���������Ѱ� ����
			
			if (_player.sight)
			{
				if (_frameIndex == 0) { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 3); }
				_player.hit->setFrameY(0);
				if (_frameCount % 80 < 50 && _frameIndex == 0) 
				{
					if (_player.viewX == 0 && _player.x > 37) { _player.x --; }
					else if (_player.cameraRc.left < 0) { _player.viewX --; }
					else { _player.x --; }
				}
				if (_frameCount == 80 || _frameCount >= 120)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 0;
						_player._state = pIDLE;
						_player.y = 460;
					}
					_player.hit->setFrameX(_frameIndex);
				}
			}
			else
			{
				if (_frameIndex == 0) { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 3); }
				_player.hit->setFrameY(1);
				if (_frameCount % 80 < 50 && _frameIndex == 0)
				{
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x ++; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX ++; }
					else { _player.x ++; }
				}
				if (_frameCount == 80 || _frameCount >= 120)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 0;
						_player._state = pIDLE;
						_player.y = 460;
					}
					_player.hit->setFrameX(_frameIndex);
				}
			}
			break;
		}
	}
	//��Ʋ�� �ƴ� ��
	else
	{
		// �÷��̾ �ȴ� ���¶��
		if (_player._state == pWALK)
		{
			// _directP�� �ٶ󺸴� �����ε� �ٶ󺸴� ���⿡ ����
			// �������̹����� Y��ǥ�� �޶���.
			switch (_direct)
			{
				//����Ű�� ������ ��
			case 0:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
				//�Ʒ���Ű�� ������ ��
			case 1:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
				//����Ű�� ������ ��
			case 2:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(2);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
				//������Ű�� ������ ��
			case 3:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(3);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
			}
		}
	}
}


void player::setAction(int pattern)
{
	tagstate state;
	if (pattern == 1) { state = pIDLE; }
	else if (pattern == 2) { state = pRUN; }
	else if (pattern == 3) { state = pHIT; }
	else if (pattern == 4) { state = pWALK; }
	else if (pattern == 5) { state = pJUMP; }
	else if (pattern == 6) { state = pATTACK; }
	else if (pattern == 7) { state = pGUARD; }
	else if (pattern == 8) { state = pDEAD; }
	else if (pattern == 8) { state = pWIN; }
	if (_player._state != state)
	{
		_frameIndex = 0;
	}
	_player._state = state;
}

void player::playerWin()
{
	if (_player._state != pWIN && !(_player._state == pJUMP || _player._state == pATTACK))
	{
		_frameIndex = 0;
		_frameCount = 0;
		_player._state = pWIN;
	}
}
void player::playerHit()
{
	_player.hp--;
	if (_player.hp > 0)
	{
		_player.gravity = 3.f;
		_player._state = pHIT;
	}
	_frameIndex = 0;
	_frameCount = 0;
}


void player::setPlayerRect(int x, int y)
{
	_player.inGameX = x;
	_player.inGameY = y;
	_player.rc = RectMakeCenter(_player.inGameX, _player.inGameY, 64, 128);
}


void player::settingTagPlayer()
{

	//�̹��� �ʱ�ȭ
	_player.idle = IMAGEMANAGER->addFrameImage("mIdle", "Images/mainplayer/idle.bmp", 150, 156, 2, 2);
	_player.walk = IMAGEMANAGER->addFrameImage("walk", "Images/mainplayer/walk.bmp", 360, 156, 4, 2);
	_player.run = IMAGEMANAGER->addFrameImage("run", "Images/mainplayer/run&stop.bmp", 450, 188, 5, 2);
	_player.guard = IMAGEMANAGER->addFrameImage("guard", "Images/mainplayer/guard.bmp", 66, 156, 1, 2);

	//���ݸ��
	_player.atkSlash = IMAGEMANAGER->addFrameImage("slash", "Images/mainplayer/atk_slash.bmp", 525, 262, 5, 2);
	//_player.atkstab = IMAGEMANAGER->addFrameImage("stab", "Images/mainplayer/atk_stab.bmp", 396, 120, 4, 2);
	_player.jump = IMAGEMANAGER->addFrameImage("jump", "Images/mainplayer/jump_slash.bmp", 445, 262, 5, 2);

	_player.dead = IMAGEMANAGER->addFrameImage("dead", "Images/mainplayer/dead.bmp", 250, 120, 4, 2);

	_player.win = IMAGEMANAGER->addFrameImage("win", "Images/mainplayer/victory.bmp", 401, 157, 4, 1);

	//��Ʈ��� �߰� - ���κ�
	_player.hit = IMAGEMANAGER->addFrameImage("hit", "Images/mainplayer/hit.bmp", 137, 140, 2, 2);

	//�÷��̾� �ʱ� ��ǥ ����
	_player.x = 200;
	_player.y = 460;
	//�÷��̾� �簢��


	_player.sight = true;		//�ʱ� ���� - ������ ����
	//_player.atkTime = 0.0f;     //Ÿ�ݽð�
	_player._state = pIDLE;		        //�ʱ� ���� - ������


	_player.speed = 3.0f;


	_player.hp = _player.maxHp = 5;			//�ʱ� ���� - ü�� 5
	_player.tp = _player.maxTp = 5;			//�ʱ� ���� - TP 5
	_player.lv = 1;
	_player.attXK = 0;
	_player.attYK = 0;

	//�ΰ��ӿ��� ����� ��ǥ�� ��Ʋ�� ��ġ�� �ȵǴϱ� ���� ������.
	_player.inGameX = (48 * 120) - WINSIZEX;
	_player.inGameY = (48 * 150) - WINSIZEY;
	//�÷��̾� ��Ʈ�� �ʱ�ȭ ���ش�.
	_player.rc = RectMakeCenter(_player.inGameX, _player.inGameY, 64, 128);
}

void player::settingPlayerDoorRect()
{
	//������ ���� render�� frameRender�� ����.
	//�ñ��ϸ� �ű� ������.
	//�ٸ� rectũ�Ⱑ �ΰ� Ÿ�� ũ���� 48 * 2��ŭ �� ũ�Ƿ�
	//�װ��� �����Ͽ� �����.

	//���� �÷��̾��� x���� WINSIZEX / 2���� ũ��, (48 * 120 - WINSIZEX / 2)���� ������(x���� ����� ��)
	if (_player.inGameX >= WINSIZEX / 2 && _player.inGameX <= (48 * 120 - WINSIZEX / 2))
	{
		//���� y���� ������
		if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
		{
			_playerDoorRc = RectMake(WINSIZEX / 2 - 80, WINSIZEY / 2 - 112, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y���� ���ʿ� ġ������ �ִٸ�
		else if (_player.inGameY < WINSIZEY / 2)
		{
			_playerDoorRc = RectMake(WINSIZEX / 2 - 80, _player.rc.top - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y���� �Ʒ��ʿ� ġ������ �ִٸ�
		else
		{
			_playerDoorRc = RectMake(WINSIZEX / 2 - 80, _player.rc.top - (48 * 150 - WINSIZEY) - 48, 64 + 48 * 2, 128 + 48 * 2);
		}

	}
	//���� �÷��̾��� y���� WINSIZEY / 2���� ũ��, (48 * 150 - WINSIZEY / 2)���� ���� ��(y���� ����� ��)
	else if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
	{
		//���� x���� �����̶��
		if (_player.inGameX < WINSIZEX / 2)
		{
			_playerDoorRc = RectMake(_player.rc.left - 48, WINSIZEY / 2 - 112, 64 + 48 * 2, 128 + 48 * 2);
		}
		//���� x���� �������̶��
		else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
		{
			_playerDoorRc = RectMake(_player.rc.left - (48 * 120 - WINSIZEX) - 48, WINSIZEY / 2 - 112, 64 + 48 * 2, 128 + 48 * 2);
		}
	}
	//�÷��̾� x�� ���ʿ� ġ������ ���� ��
	else if (_player.inGameX < WINSIZEX / 2)
	{
		//���� y�� ���ʿ� ġ������ �ִٸ�
		if (_player.inGameY < WINSIZEY / 2)
		{
			_playerDoorRc = RectMake(_player.rc.left - 48, _player.rc.top - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y���� �Ʒ��ʿ� ġ������ �ִٸ�
		else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
		{
			_playerDoorRc = RectMake(_player.rc.left - 48, _player.rc.top - (48 * 150 - WINSIZEY) - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
	}
	//�÷��̾� x�� �����ʿ� ġ������ ���� ��
	else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
	{
		//���� y�� ���ʿ� ġ������ �ִٸ�
		if (_player.inGameY < WINSIZEY / 2)
		{
			_playerDoorRc = RectMake(_player.rc.left - (48 * 120 - WINSIZEX) - 48, _player.rc.top - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y���� �Ʒ��ʿ� ġ������ �ִٸ�
		else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
		{
			_playerDoorRc = RectMake(_player.rc.left - (48 * 120 - WINSIZEX) - 48, _player.rc.top - (48 * 150 - WINSIZEY) - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
	}
}

void player::spinPlayer()
{
	//stateWindow�� ���̵Ǹ� �÷��̾ update ���ϱ� ������ ���⼭ ������ī���͸� ������Ų��.
	_frameCount++;

	//40�������� ������ ���� ���� ������ �ٲ��ش�.
	//������ �Ʒ� �� �� ���̴�.
	if (_frameCount % 500 == 0)
	{
		if (_direct == 0)
			_direct = 3;
		else if (_direct == 1)
			_direct++;
		else if (_direct == 2)
			_direct = 0;
		else
			_direct = 1;
	}
	//
	this->animation();
}

HRESULT subplayer::init()
{

								//�̹��� �ʱ�ȭ
	//��� ���
	_subPlayer.idle = IMAGEMANAGER->addFrameImage("subIdle", "Images/subplayer/chester_battel_idle.bmp", 154, 182, 2, 2);
	//�ȱ� ���
	_subPlayer.walk = IMAGEMANAGER->addFrameImage("subWalk", "Images/subplayer/chester_battel_walk.bmp", 328, 184, 4, 2);
	//�޸��� ���
	_subPlayer.run = IMAGEMANAGER->addFrameImage("subRun", "Images/subplayer/chester_battel_run.bmp", 344, 172, 4, 2);
	//���Ÿ� ���� ���
	_subPlayer.atkshot = IMAGEMANAGER->addFrameImage("subShot", "Images/subplayer/chester_battel_shoot.bmp", 728, 198, 8, 2);
	//���� ���� ���
	_subPlayer.atkmelee = IMAGEMANAGER->addFrameImage("subMelee", "Images/subplayer/chester_battel_physical.bmp", 202,180,2, 2);
	//��� ���
	_subPlayer.dead = IMAGEMANAGER->addFrameImage("subDead", "Images/subplayer/chester_battel_dead.bmp", 279, 210, 3, 2);
	//�¸� ���
	_subPlayer.win = IMAGEMANAGER->addFrameImage("subWin", "Images/subplayer/chester_battel_win.bmp", 285, 236, 3, 2);
	//ȭ�� �̹���
	_arrow._img = IMAGEMANAGER->addFrameImage("arrow", "Images/subplayer/arrow.bmp", 76, 22, 1, 2);
								//�̹��� �ʱ�ȭ ��
	_walkingDirect = IMAGEMANAGER->addFrameImage("chester", "Images/subplayer/chester_walking_direct.bmp", 165, 256, 5, 4);




	//�÷��̾� �ʱ� ��ǥ ����
	_subPlayer.x = 200;
	_subPlayer.y = 414;
	//�÷��̾� �簢��



	_subPlayer.sight = true;	//�ʱ� ���� - ������ ����
	_subPlayer._state = pIDLE;		        //�ʱ� ���� - ������

	_arrow._chargeTime = 0.0f;	//ȭ���غ� �ð�. (���� �ð��� �����ϸ� �߻�)
	_arrow._bShoot = false;		//ȭ���� �߻�Ǿ����� �Ǵ��ϴ� bool ����.
								//true�� ��� �߻�� ������ �Ǵ��ϹǷ� false�� �ʱ�ȭ.
	_arrow._speed = 0.0f;		//ȭ���� ���ư��� �ӵ� �ʱ�ȭ.
	_partyDistance = 0.0f;
	_enemyDistance = 0.0f;

	_melee = false;				//�Ÿ��� ���� �Ÿ��� �ɰ�� true���� �Ǿ� ���ݽ� ������������ ��ȯ

	_subPlayer.hp = _subPlayer.maxHp = 5;			//�ʱ� ���� - ü�� 5
	_subPlayer.tp = _subPlayer.maxTp = 5;
	_subPlayer.lv = 1;
	_subPlayer.attXK = 0;
	_subPlayer.attYK = 0;


	//�������̹����ʱ�ȭ
	_frameCount = 0;
	_frameIndex = 0;

	return S_OK;
}

void subplayer::release()
{

}

void subplayer::update(int playerViewX)
{
	this->animation();


	//ai�� ��ġ
	_subPlayer.viewX = _subPlayer.x - playerViewX;
	_subPlayer.rc = RectMake(_subPlayer.viewX, _subPlayer.y, 77, 91);
	
	//�̵� ���¿� ���� �ӵ� ����
	if (_subPlayer._state == pWALK) 
	{
		_subPlayer.speed = 1.0f;	//pWALK�� ���� �ӵ��� 1.0f�� ����
		if (_subPlayer.sight) 
		{
			if (_subPlayer.rc.right < 0) { _subPlayer.viewX += _subPlayer.speed; }
			else { _subPlayer.x += _subPlayer.speed; }
		}
		else 
		{
			if (_subPlayer.rc.left > WINSIZEX) { _subPlayer.viewX -= _subPlayer.speed; }
			else { _subPlayer.x -= _subPlayer.speed; }
		}
	}
	if (_subPlayer._state == pRUN)
	{
		_subPlayer.speed = 3.0f; 	//pRun�� ���� �ӵ��� 3.0f�� ����
		if (_subPlayer.sight)
		{
			if (_subPlayer.rc.left < 0) { _subPlayer.viewX += _subPlayer.speed; }
			else { _subPlayer.x += _subPlayer.speed; }
		}
		else
		{
			if (_subPlayer.rc.right > WINSIZEX) { _subPlayer.viewX -= _subPlayer.speed; }
			else { _subPlayer.x -= _subPlayer.speed; }
		}
	}
	
	//�Ÿ�����
	if (_partyDistance > 200)
	{
		_subPlayer._state = pRUN;
		_arrow._chargeTime = 0.0f;
	}
	else if (_partyDistance > 100)
	{
		_subPlayer._state = pWALK;
		_arrow._chargeTime = 0.0f;
	}
	else
	{
		if (_enemyDistance < 100) 
		{ 
			_melee = true; 
			_subPlayer._state = pATTACK;
		}
		else if (_enemyDistance < 500)
		{
			_melee = false;
			_subPlayer._state = pATTACK;
		}
		else
		{
			_subPlayer._state = pIDLE;
			_arrow._chargeTime = 0.0f;
		}
	}

	//����
	if (_subPlayer._state == pATTACK)
	{
		//���� ������ ��� ���� ������ �Ѵ�.
		if(_melee)
		{
			_frameIndex = 0;
			if (_subPlayer.sight == true) { _subPlayer.attack = RectMake(_subPlayer.rc.right, _subPlayer.y, 20, 91); }
			else { _subPlayer.attack = RectMake(_subPlayer.rc.left-20, _subPlayer.y, _subPlayer.rc.left, 91); }
		}
		//������ �ƴҽ� Ȱ�� ���.
		else
		{
			//ȭ�� ���� �ð��� 30.0 �̻��̰� �߻���� �ʾ��� ��
			if (_arrow._chargeTime > 10.0f && !_arrow._bShoot)
			{
				_arrow._bShoot = true;		//ȭ�� �߻�
				_arrow._chargeTime = 0.0f;	//ȭ�� ���� �ð��� �ʱ�ȭ.
				_arrow._speed = 2.1f;
				_arrow._point.x = (float(_subPlayer.rc.left) + float((_subPlayer.rc.right - _subPlayer.rc.left) / 2));	//x��ǥ
				_arrow._point.y = (float(_subPlayer.rc.top) + float((_subPlayer.rc.bottom - _subPlayer.rc.top) / 2));	//y��ǥ
				_arrow._rc = RectMakeCenter(_arrow._point.x - 1, _arrow._point.y - 1, 17, 11);		//ȭ�� Rect ����.
				_arrow._flyDirect = _subPlayer.sight;
			}
			else
			{
				//ȭ������
				_arrow._chargeTime += 0.1f;
			}
		}
	}


	//ȭ���� ���ư��� ȭ���� ��ǥ �̵�
	
	if (_arrow._bShoot)
	{
		if (_arrow._flyDirect == true) { _arrow._point.x += cosf(PI / 2) * 2 + _arrow._speed; }
		else { _arrow._point.x -= cosf(PI / 2) * 2 + _arrow._speed; }
		//������ y�� �Ⱥ��ϴϱ� �ּ�ó��
		//_arrow._point.y += -sinf(PI / 2) * 2;
		//if (_arrow._point.y >= 500) { _arrow._bShoot = false; }
		_arrow._rc = RectMakeCenter(_arrow._point.x - 1, _arrow._point.y - 1, 17, 11); //ȭ�� POINT �̵���������
																					   //ȭ�� RECT�� ��
	}

}

void subplayer::render()
{
	Rectangle(getMemDC(), _subPlayer.rc);

	switch (_subPlayer._state)
	{
	case pIDLE:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subIdle")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		else
		{
			IMAGEMANAGER->findImage("subIdle")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		break;
	case pWALK:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subWalk")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		else
		{
			IMAGEMANAGER->findImage("subWalk")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		break;
	case pATTACK:
		if (_melee)
		{
			Rectangle(getMemDC(), _subPlayer.attack);
			if (_subPlayer.sight)
			{
				IMAGEMANAGER->findImage("subMelee")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
			}
			else
			{
				IMAGEMANAGER->findImage("subMelee")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
			}
		}
		else
		{
			if (_subPlayer.sight)
			{
				IMAGEMANAGER->findImage("subShot")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
			}
			else
			{
				IMAGEMANAGER->findImage("subShot")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);

			}
		}
		break;
	case pRUN:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subRun")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		else
		{
			IMAGEMANAGER->findImage("subRun")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		break;
	default:
		break;
	}
	
	if(_arrow._bShoot)
	{
		IMAGEMANAGER->findImage("arrow")->frameRender(getMemDC(), _arrow._point.x, _arrow._point.y);
	}

	char chr[100];
	sprintf_s(chr, "�Ÿ� : %f", _enemyDistance);
	TextOut(getMemDC(), 100, 150, chr, strlen(chr));

	char chr1[100];
	sprintf_s(chr1, "ȭ�������ð� : %f", _arrow._chargeTime);
	TextOut(getMemDC(), 100, 200, chr1, strlen(chr1));
}

void subplayer::animation()
{
	switch (_subPlayer._state)
	{
	case pIDLE:				  //������
	{
		if (_subPlayer.sight)
		{
			_frameCount++;
			_subPlayer.idle->setFrameY(0);
			if (_frameCount % 16 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 2)
				{
					_frameIndex = 0;
				}
				_subPlayer.idle->setFrameX(_frameIndex);
			}
		}
		else
		{
			_frameCount++;
			_subPlayer.idle->setFrameY(1);
			if (_frameCount % 16 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 1;
				}
				_subPlayer.idle->setFrameX(_frameIndex);
			}
		}
		break;
	}
	case pWALK:		//�ȱ�
	{
		if (_subPlayer.sight)
		{
			_frameCount++;
			_subPlayer.walk->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 4)
				{
					_frameIndex = 0;
				}
				_subPlayer.walk->setFrameX(_frameIndex);
			}
		}
		else
		{
			_frameCount++;
			_subPlayer.walk->setFrameY(1);
			if (_frameCount % 8 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 3;
				}
				_subPlayer.walk->setFrameX(_frameIndex);
			}
		}
		break;
	}
	case pATTACK:
		if (_melee)	//���� ������ �� ��
		{
			_frameCount++;
			if (_subPlayer.sight)
			{
				_subPlayer.atkmelee->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
						//���� ������ �̹��� �������� 2��
						//���� _frameIndex�� 1���� ū ���� ������ ���� ������ �Ǵ��Ѵ�.
					{
						_frameCount = 0;	//_frameCount�� 0���� �ʱ�ȭ
						_frameIndex = 0;	//_frameIndex�� 0���� �ʱ�ȭ
						_subPlayer._state = pIDLE;		//�����·� ��ȯ
					}
					_subPlayer.atkmelee->setFrameX(_frameIndex);
				}
			}
			else
			{
				_subPlayer.atkmelee->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0)
						//���� ������ �̹��� �������� 2��
						//���� _frameIndex�� 1���� ū ���� ������ ���� ������ �Ǵ��Ѵ�.
					{
						_frameCount = 0;	//_frameCount�� 0���� �ʱ�ȭ
						_frameIndex = 1;	//_frameIndex�� 0���� �ʱ�ȭ
						_subPlayer._state = pIDLE;		//�����·� ��ȯ
					}
					_subPlayer.atkmelee->setFrameX(_frameIndex);
				}
			}
		}
		else	//���Ÿ� ������ �� ��
		{
			if (_subPlayer.sight)
			{
				_frameCount++;
				_subPlayer.atkshot->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_arrow._bShoot == false) { _frameIndex = 2; }	//�߻縦 ���� ���ߴٸ� ������ �ݺ�
					if (_frameIndex > 7)
						//���Ÿ� ������ �̹��� �������� 8��
						//���� _frameIndex�� 7���� ū ���� ������ ���� ������ �Ǵ��Ѵ�.
					{
						_frameCount = 0;	//_frameCount�� 0���� �ʱ�ȭ
						_frameIndex = 0;						//_frameIndex�� 0���� �ʱ�ȭ
						_subPlayer._state = pIDLE;		//�����·� ��ȯ
					}
					_subPlayer.atkshot->setFrameX(_frameIndex);
				}
			}
			else
			{
				_frameCount++;
				_subPlayer.atkshot->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex--;
					if (_arrow._bShoot == false) { _frameIndex = 4; }	//�߻縦 ���� ���ߴٸ� ������ �ݺ�
					if (_frameIndex < 1)
						//���Ÿ� ������ �̹��� �������� 8��
						//���� _frameIndex�� 7���� ū ���� ������ ���� ������ �Ǵ��Ѵ�.
					{
						_frameCount = 0;	//_frameCount�� 0���� �ʱ�ȭ
						_frameIndex = 0;	//_frameIndex�� 0���� �ʱ�ȭ
						_subPlayer._state = pIDLE;		//�����·� ��ȯ
					}
					_subPlayer.atkshot->setFrameX(_frameIndex);
				}
			}
		}
		break;

	case pRUN:
	{
		if(_subPlayer.sight)
		{
			_frameCount++;
			_subPlayer.run->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 4)
				{
					_frameIndex = 0;
				}
				_subPlayer.run->setFrameX(_frameIndex);
			}
		}
		else
		{
			_frameCount++;
			_subPlayer.run->setFrameY(1);
			if (_frameCount % 8 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 3;
				}
				_subPlayer.run->setFrameX(_frameIndex);
			}
		}
		break;
	}
	default:
		break;
	}

	if (_subPlayer.sight) { _arrow._img->setFrameY(0); }
	else { _arrow._img->setFrameY(1); }
}

void subplayer::walkingInfo()
//����â���� ���� �ִϸ��̼� ���
{
	_frameCount++;

	switch(_direct%4)
	{
	case 0:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 3;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	case 1:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 2;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	case 2:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 0;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	case 3:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 1;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	default:
		break;
	}
}

void subplayer::checkDistanceWithPlayer(float x)
{
	_partyDistance = sqrt(powf(x - _subPlayer.viewX, 2.0f));
	if (x < _subPlayer.viewX) { _subPlayer.sight = 0; }
	else { _subPlayer.sight = 1; }
}

void subplayer::checkDistanceWithEnemy(float x)
{
	_enemyDistance = sqrt(powf(x - _subPlayer.viewX, 2.0f));
	if (_subPlayer._state == pATTACK)
	{
		if (x < _subPlayer.viewX) { _subPlayer.sight = 0; }
		else { _subPlayer.sight = 1; }
	}
}

void subplayer::checkArrowHitTheEnemy(bool b)
{
	if (_arrow._bShoot == true)
	{
		_arrow._bShoot = !b;	//�浹������ ȭ�� �߻� false ó��
								//�ƴϸ� ��� ���ư�
	}

}
