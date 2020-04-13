#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	// �÷��̾� ����ü�� init��Ű�� �ʱ�ȭ �����ش�.
	this->settingTagPlayer();

	_stage = RectMake(0, 500, WINSIZEX, WINSIZEY);

	//�������̹����ʱ�ȭ
	_frameCount = 0;
	_frameIndex = 0;

	//�����ð� �ʱ�ȭ
	//_immoTime = 0;

	//_enemyHP = 3;


	//_enemyX = 500;
	//_enemyY = 400;

	// ������ ������ �� �������� �ƴϴ�.
	_isBattle = false;
	// �÷��̾�� ���� ���� ������ �� �Ʒ��� �ٶ󺸰� �ִ�.
	_direct = 1;

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
		if (!(_state == pATTACK || _state == pJUMP))
		{
			_player.attXK = 0;
			_player.attYK = 0;
		}
		if (_player.sight == true)
		{
			_player.attack = RectMake(_player.rc.right - 20, _player.rc.top, _player.attXK, _player.attYK);
			//_player.jumpAttack = RectMake(_rcPlayer.right - 20, _rcPlayer.top, 50, 160);
		}
		else if (_player.sight == false)
		{
			_player.attack = RectMake(_player.rc.left - 20, _player.rc.top, _player.attXK, _player.attYK);
			//_player.jumpAttack = RectMake(_rcPlayer.left - 20, _rcPlayer.top, 50, 160);
		}

		if (_state == pWALK)
		{
			_player.speed = 3.0f;
		}
		else if (_state == pRUN)
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

		//sight left & walk left
		if (INPUT->GetKey(VK_LEFT))
		{
			if (_state == pATTACK)
			{
				_state = pATTACK;
			}
			else if (_state == pGUARD)
			{
				_player.sight = 0;
				_state = pGUARD;
			}
			else if (_state == pJUMP)
			{
				_state = pJUMP;
				_player.x -= 3;
			}
			else
			{
				if (INPUT->GetKey(VK_SHIFT))
				{
					_player.sight = 0;				 //�÷��̾� ���� - ����
					_state = pRUN;			 //�÷��̾� ���� - �ٱ�
					_player.x -= _player.speed;                    //�÷��̾� ��ǥ ��ȭ
				}
				else
				{
					_player.sight = 0;				 //�÷��̾� ���� - ����
					_state = pWALK;			 //�÷��̾� ���� - �ȱ�
					_player.x -= _player.speed;                    //�÷��̾� ��ǥ ��ȭ
				}
			}
		}
		//state idle
		if (INPUT->GetKeyUp(VK_LEFT) && _state != pATTACK)
		{

			if (_state != pGUARD)
			{
				_state = pIDLE;
			}
		}
		//sight right & walk right
		if (INPUT->GetKey(VK_RIGHT))
		{
			if (_state == pATTACK)
			{
				_state = pATTACK;
			}
			else if (_state == pGUARD)
			{
				_player.sight = 1;
				_state = pGUARD;
			}
			else if (_state == pJUMP)
			{
				_state = pJUMP;
				_player.x += 3;
			}
			else
			{
				if (INPUT->GetKey(VK_SHIFT))
				{
					_player.sight = 1;				 //�÷��̾� ���� - ������
					_state = pRUN;			         //�÷��̾� ���� - �ٱ�
					_player.x += _player.speed;                  //�÷��̾� ��ǥ ��ȭ
				}
				else
				{
					_player.sight = 1;				 //�÷��̾� ���� - ������
					_state = pWALK;			         //�÷��̾� ���� - �ȱ�
					_player.x += _player.speed;                  //�÷��̾� ��ǥ ��ȭ
				}
			}
		}
		//state idle
		if (INPUT->GetKeyUp(VK_RIGHT) && _state != pATTACK)
		{

			if (_state != pGUARD)
			{
				_state = pIDLE;
			}
		}


		//test - state attack -> ����� ���, �����ÿ��� ���� ���� �������� �߰�����
		if (INPUT->GetKeyDown('Z') && _state != pDEAD && _state != pJUMP)
		{
			_state = pATTACK;
			if (_state != pATTACK)
			{
				_frameIndex = 0;
			}

			_player.attXK = 50;
			_player.attYK = 130;

		}

		//test - state guard
		if (INPUT->GetKey('X') && _state != pJUMP)
		{
			_state = pGUARD;
		}
		if (INPUT->GetKeyUp('X'))
		{
			_state = pIDLE;
		}

		// state jump
		if (INPUT->GetKeyDown('C') && _state != pJUMP)
		{
			_frameIndex = 0;
			_state = pJUMP;
			_player.gravity = 0.0f;
			_player.attXK = 50;
			_player.attYK = 130;
		}

		if (_state == pJUMP)
		{
			_player.x += cosf(PI / 2) * 1;
			_player.y += -sinf(PI / 2) * 5 + _player.gravity;
			_player.gravity += 0.1f;
		}



		//test - state win
		if (INPUT->GetKeyDown(VK_F5))
		{
			_state = pWIN;
		}

		//�ٴڿ� ��� �Ǿ�����
		if (_player.y > 460 && _state == pJUMP)
		{
			_player.gravity = 0.0f;
			_state = pIDLE;
			_player.y = 460;
		}
		//���߿��� �ٸ� ����� ������� �ʵ��� ����
		if (_player.y < 460 && _state != pJUMP)
		{
			_state = pJUMP;
		}

		//�÷��̾� ���
		if (_player.hp <= 0)
		{
			_state = pDEAD;
		}



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
			_state = pWALK;
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
			_state = pIDLE;
		}
		// �Ʒ���Ű�� ������ ��
		if (INPUT->GetKey(VK_DOWN))
		{
			//�����̸� ���� ���¸� walk�� �ٲ��ش�.
			_state = pWALK;
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
			_state = pIDLE;
		}
		// ����Ű�� ������ ��
		if (INPUT->GetKey(VK_LEFT))
		{
			//�����̸� ���� ���¸� walk�� �ٲ��ش�.
			_state = pWALK;
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
			_state = pIDLE;
		}
		// ������Ű�� ������ ��
		if (INPUT->GetKey(VK_RIGHT))
		{
			//�����̸� ���� ���¸� walk�� �ٲ��ش�.
			_state = pWALK;
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
			_state = pIDLE;
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
		Rectangle(getMemDC(), _stage);

		Rectangle(getMemDC(), _player.rc);		//�÷��̾� Ÿ�ݹ��� �簢��

		Rectangle(getMemDC(), _player.attack);		//�÷��̾� Ÿ�ݹ��� �簢��

		this->animation();					//�÷��̾� ��� �ִϸ��̼�
											//��Ʋ�� �� �ִϸ��̼����� �����ϴϱ� �ڿ� �д�.

		char chr1[100];
		sprintf(chr1, "player hp : %d", _player.hp);
		TextOut(getMemDC(), 100, 720, chr1, strlen(chr1));
	}
	else
	{
		this->animation();					//�÷��̾� ��� �ִϸ��̼�
											//��Ʋ�� �ƴҶ� ������X, Y���� �ٲ��ֱ� ������ ���� ���� �Լ��� �ҷ��ش�.

		//�� �浹�� ���� ��Ʈ �����ֱ�
		FrameRect(getMemDC(), _playerDoorRc, RGB(255, 0, 0));

		// �÷��̾ �ȴ� ���¶��
		if (_state == pWALK)
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
		switch (_state)
		{
		case pIDLE:		//������
			//��
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("mIdle", getMemDC(), _player.rc.left, _player.rc.top);
				_frameCount++;
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
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("mIdle", getMemDC(), _player.rc.left, _player.rc.top);
				_frameCount++;
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
				IMAGEMANAGER->frameRender("walk", getMemDC(), _player.rc.left - 10, _player.rc.top);
				_frameCount++;
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
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("walk", getMemDC(), _player.rc.left + 10, _player.rc.top);
				_frameCount++;
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
				IMAGEMANAGER->frameRender("run", getMemDC(), _player.rc.left - 10, _player.rc.top - 10);
				_frameCount++;
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
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("run", getMemDC(), _player.rc.left, _player.rc.top - 10);
				_frameCount++;
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
				IMAGEMANAGER->frameRender("slash", getMemDC(), _player.rc.left - 15, _player.rc.top - 20);
				_frameCount++;
				_player.atkSlash->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("slash")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameCount = 0;
						_frameIndex = 0;
						_state = pIDLE;	//�ѹ������� ���´���ڼ���
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("slash", getMemDC(), _player.rc.left - 10, _player.rc.top - 15);
				_frameCount++;
				_player.atkSlash->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("slash")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
						_state = pIDLE;
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			break;
		case pJUMP:
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("jump", getMemDC(), _player.rc.left, _player.rc.top - 20);
				_frameCount++;
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
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("jump", getMemDC(), _player.rc.left, _player.rc.top - 20);
				_frameCount++;
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
				_frameCount++;
				_player.atkSlash->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("guard")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 1)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("guard", getMemDC(), _player.rc.left, _player.rc.top);
				_frameCount++;
				_player.atkSlash->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("guard")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 1)
					{
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			break;
		case pDEAD:		//����ÿ��� hp = 0�̵Ǿ� ����ϸ� ���ɻ��� ���� - ���� ����۵� ���� ����
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top);
				_frameCount++;
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
			if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top);
				_frameCount++;
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
			_frameCount++;
			_player.win->setFrameY(0);
			if (_frameCount % 20 == 0)
			{
				IMAGEMANAGER->findImage("win")->setFrameY(0);
				_frameIndex++;
				_player.win->setFrameX(_frameIndex);
			}
			break;
		}
	}
	//��Ʋ�� �ƴ� ��
	else
	{
	// �÷��̾ �ȴ� ���¶��
	if (_state == pWALK)
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

	_player.dead = IMAGEMANAGER->addFrameImage("dead", "Images/mainplayer/dead.bmp", 264, 156, 4, 2);

	_player.win = IMAGEMANAGER->addFrameImage("win", "Images/mainplayer/victory.bmp", 401, 157, 4, 1);


	//�÷��̾� �ʱ� ��ǥ ����
	_player.x = 200;
	_player.y = 460;
	//�÷��̾� �簢��


	_player.sight = true;		//�ʱ� ���� - ������ ����
	//_player.atkTime = 0.0f;     //Ÿ�ݽð�
	_state = pIDLE;		        //�ʱ� ���� - ������


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

	_mainplayer = new player;
	_mainplayer->init();


	//�̹��� �ʱ�ȭ
	_player.idle = IMAGEMANAGER->addFrameImage("subIdle", "Images/subplayer/chester_battel_idle.bmp", 288, 180, 2, 1);
	_player.walk = IMAGEMANAGER->addFrameImage("subWalk", "Images/subplayer/chester_battel_walk.bmp", 576, 180, 4, 1);
	//_player.run = IMAGEMANAGER->addFrameImage("run", "Images/subplayer/chester_battel_run.bmp", 576, 180, 4, 1);
	//_player.guard = IMAGEMANAGER->addFrameImage("guard", "Images/mainplayer/guard.bmp", 110, 260, 1, 1);

	//���ݸ��
	_player.atkshot = IMAGEMANAGER->addFrameImage("subShot", "Images/subplayer/chester_battel_shoot.bmp", 1152, 180, 8, 1);
	_player.atkmelee = IMAGEMANAGER->addFrameImage("subMelee", "Images/subplayer/chester_battel_physical.bmp", 288, 180, 2, 1);
	//_player.atkstab = IMAGEMANAGER->addFrameImage("stab", "Images/subplayer/mainplayer/atk_stab.bmp", 396, 120, 4, 2);
	//_player.jump = IMAGEMANAGER->addFrameImage("jump", "Images/mainplayer/jump_slash.bmp", 749, 347, 5, 1);

	_player.dead = IMAGEMANAGER->addFrameImage("subDead", "Images/subplayer/chester_battel_dead.bmp", 432, 180, 3, 1);

	_player.win = IMAGEMANAGER->addFrameImage("subWin", "Images/subplayer/chester_battel_win.bmp", 432, 180, 3, 1);


	_arrowImg = IMAGEMANAGER->addImage("arrow", "Images/subplayer/arrow.bmp", 76, 11);



	//�÷��̾� �ʱ� ��ǥ ����
	_player.x = 100;
	_player.y = 370;
	//�÷��̾� �簢��



	_player.sight = true;		//�ʱ� ���� - ������ ����

	_state = pIDLE;		        //�ʱ� ���� - ������

	_chargeTime = 0.0f;			//ȭ���غ� �ð�(�����ð��� ä��� �߻��� ����)
	_arrowIs = false;			//ȭ��ȳ��ư� ���� true�� �ɽ� ȭ���� ���ư�����
	_speed = 0.0f;

	_melee = false;					//�Ÿ��� ���� �Ÿ��� �ɰ�� true���� �Ǿ� ���ݽ� ������������ ��ȯ

	//if (_state == pWALK)
	//{
	//	_player.speed = 1.0f;
	//}
	//else if (_state == pRUN)
	//{
	//	_player.speed = 3.0f;
	//}

	_player.hp = 5;			//�ʱ� ���� - ü�� 5

	//�������̹����ʱ�ȭ
	_frameCount = 0;
	_frameIndex = 0;

	return S_OK;
}

void subplayer::release()
{
	_mainplayer->release();
	SAFE_DELETE(_mainplayer);
}

void subplayer::update()
{

	//ai�� ��ġ
	_rcPlayer = RectMake(_player.x, _player.y, 125, 130);

	//������ ��ġ
	_cX = (float(_rcPlayer.left) + float((_rcPlayer.right - _rcPlayer.left) / 2));
	_cY = (float(_rcPlayer.top) + float((_rcPlayer.bottom - _rcPlayer.top) / 2));

	//�����÷��̾��� ��ġ�� �ޱ�����
	_mainplayer->update();


	//�ǽð� �Ÿ�
	//ai�� ���� �Ÿ�
	//_distance = sqrt(pow(_cX - _mainplayer->getenemyCenterx(), 2) + pow(_cY - _mainplayer->getenemyCentery(), 2));


	//ȭ������
	_chargeTime += 0.1f;

	//�����Ϸ�
	if (_chargeTime > 30.0f&& _arrowIs == false)
	{
		_chargeTime = 0.0f;
		_state = pATTACK;
	}
	else if (_frameIndex == 0)
	{
		_state = pIDLE;
	}

	//�Ÿ�����
	if (_distance > 700)
	{
		_state = pWALK;
		_player.x++;
	}
	else if(_distance)
	{
		
	}

	//����
	if (_state == pATTACK)
	{
		//������ �ƴҽ� Ȱ�� ���.
		if (_melee == false)
		{
			//ȭ���� ���ư��ϴ�.
			_arrowIs = true;
		}
		if (_melee == true)
		{

		}
	}


	//ȭ���� ���ư��� ȭ���� ��ǥ �̵�
	if (_arrowIs == true)
	{
		_cX += cosf(PI / 2) * 2 + _speed;
		_cY += -sinf(PI / 2) * 2;
		_speed += 2.1f;
	}

	if (INPUT->GetKey('W'))
	{
		_cX += cosf(PI / 2) * 2 + _speed;
	}
	if (INPUT->GetKey('S'))
	{
		_cX -= cosf(PI / 2) * 2 + _speed;
	}

	//ȭ���浹
	//RECT temp;
	//if (IntersectRect(&temp, &_mainplayer->getenemyRect(), &_arrow))
	//{
	//	_arrowIs = false;
	//}

	//ai ������ Ȯ�ο�
	if (INPUT->GetKey('A'))
	{
		_player.x--;
	}
	if (INPUT->GetKey('D'))
	{
		_player.x++;
	}

}

void subplayer::render()
{
	Rectangle(getMemDC(), _rcPlayer);






	this->animation();
	_arrow = RectMakeCenter(_cX - 1, _cY - 1, 17, 11);

	//if (_arrowIs == true)
	//{
	//	Rectangle(getMemDC(), _arrow);
	//	LineMake(getMemDC(), _cX, _cY, _mainplayer->getenemyCenterx(), _mainplayer->getenemyCentery());
	//	IMAGEMANAGER->rotateRender("arrow", getMemDC(), _cX, _cY, (_cX, _cY));
	//}

	char chr[100];
	sprintf(chr, "�Ÿ� : %f", _distance);
	TextOut(getMemDC(), 100, 150, chr, strlen(chr));

	char chr1[100];
	sprintf(chr1, "ȭ�������ð� : %f", _chargeTime);
	TextOut(getMemDC(), 100, 200, chr1, strlen(chr1));
}

void subplayer::animation()
{
	switch (_state)
	{
	case pIDLE:		//������
		IMAGEMANAGER->frameRender("subIdle", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 30);
		_frameCount++;
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
		break;
	case pWALK:		//�ȱ�
		IMAGEMANAGER->frameRender("subWalk", getMemDC(), _rcPlayer.left - 20, _rcPlayer.top - 30);
		_frameCount++;
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
		break;

	case pATTACK:
		if (_melee == false)
		{
			IMAGEMANAGER->frameRender("subShot", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 30);
			_frameCount++;
			_player.atkshot->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 8)
				{
					_frameCount = 0;
					_frameIndex = 0;
					_state = pIDLE;
				}
				_player.atkshot->setFrameX(_frameIndex);
			}
		}
		else if (_melee = true)
		{
			IMAGEMANAGER->frameRender("subMelee", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 30);
			_frameCount++;
			_player.atkmelee->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 2)
				{
					_frameCount = 0;
					_frameIndex = 0;
					_state = pIDLE;
				}
				_player.atkmelee->setFrameX(_frameIndex);
			}
		}

		break;
	}
}
