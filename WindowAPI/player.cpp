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

								//�̹��� �ʱ�ȭ
	//��� ���
	_subPlayer.idle = IMAGEMANAGER->addFrameImage("subIdle", "Images/subplayer/chester_battel_idle.bmp", 288, 180, 2, 1);
	//�ȱ� ���
	_subPlayer.walk = IMAGEMANAGER->addFrameImage("subWalk", "Images/subplayer/chester_battel_walk.bmp", 576, 180, 4, 1);
	//�޸��� ���
	_subPlayer.run = IMAGEMANAGER->addFrameImage("subRun", "Images/subplayer/chester_battel_run.bmp", 576, 180, 4, 1);
	//���Ÿ� ���� ���
	_subPlayer.atkshot = IMAGEMANAGER->addFrameImage("subShot", "Images/subplayer/chester_battel_shoot.bmp", 1152, 180, 8, 1);
	//���� ���� ���
	_subPlayer.atkmelee = IMAGEMANAGER->addFrameImage("subMelee", "Images/subplayer/chester_battel_physical.bmp", 288, 180, 2, 1);
	//��� ���
	_subPlayer.dead = IMAGEMANAGER->addFrameImage("subDead", "Images/subplayer/chester_battel_dead.bmp", 432, 180, 3, 1);
	//�¸� ���
	_subPlayer.win = IMAGEMANAGER->addFrameImage("subWin", "Images/subplayer/chester_battel_win.bmp", 432, 180, 3, 1);
	//ȭ�� �̹���
	_arrow._img = IMAGEMANAGER->addImage("arrow", "Images/subplayer/arrow.bmp", 76, 11);
								//�̹��� �ʱ�ȭ ��
	_walkingDirect = IMAGEMANAGER->addFrameImage("chester", "Images/subplayer/chester_walking_direct.bmp", 165, 256, 5, 4);




	//�÷��̾� �ʱ� ��ǥ ����
	_subPlayer.x = 100;
	_subPlayer.y = 370;
	//�÷��̾� �簢��



	_subPlayer.sight = true;	//�ʱ� ���� - ������ ����
	_state = pIDLE;		        //�ʱ� ���� - ������

	_arrow._chargeTime = 0.0f;	//ȭ���غ� �ð�. (���� �ð��� �����ϸ� �߻�)
	_arrow._bShoot = false;		//ȭ���� �߻�Ǿ����� �Ǵ��ϴ� bool ����.
								//true�� ��� �߻�� ������ �Ǵ��ϹǷ� false�� �ʱ�ȭ.
	_arrow._speed = 0.0f;		//ȭ���� ���ư��� �ӵ� �ʱ�ȭ.

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

void subplayer::update()
{
	this->animation();

	//ai�� ��ġ
	_subPlayer.rc = RectMake(_subPlayer.x, _subPlayer.y, 125, 130);

	//������ ��ġ
	_arrow._point.x = (float(_subPlayer.rc.left) + float((_subPlayer.rc.right - _subPlayer.rc.left) / 2));	//x��ǥ
	_arrow._point.y = (float(_subPlayer.rc.top) + float((_subPlayer.rc.bottom - _subPlayer.rc.top) / 2));	//y��ǥ
	_arrow._rc = RectMakeCenter(_arrow._point.x - 1, _arrow._point.y - 1, 17, 11);		//ȭ�� Rect ����.

	//�ǽð� �Ÿ�
	//ai�� ���� �Ÿ�
	//_distance = sqrt(pow(_cX - _mainplayer->getenemyCenterx(), 2) + pow(_cY - _mainplayer->getenemyCentery(), 2));

	//�̵� ���¿� ���� �ӵ� ����
	if (_state == pWALK) { _subPlayer.speed = 1.0f; }	//pWALK�� ���� �ӵ��� 1.0f�� ����
	if (_state == pRUN) { _subPlayer.speed = 3.0f; }	//pRun�� ���� �ӵ��� 3.0f�� ����
	
	//�Ÿ�����
	if (_distance > 700)
	{
		_state = pWALK;
		_subPlayer.x++;
	}
	else
	{
		if (_distance >= 50) { _melee = false; }	//�Ÿ��� 50 �̻��̸� Ȱ�� ����
		else { _melee = true; }						//�Ÿ��� 50 �̸��̸� ���� ����
		_state = pATTACK;	//���� ���·� ��ȯ
	}

	//����
	if (_state == pATTACK)
	{
		//���� ������ ��� ���� ������ �Ѵ�.
		if(_melee)
		{
			_frameIndex = 0;
		}
		//������ �ƴҽ� Ȱ�� ���.
		else
		{
			//ȭ�� ���� �ð��� 30.0 �̻��̰� �߻���� �ʾ��� ��
			if (_arrow._chargeTime > 30.0f && !_arrow._bShoot)
			{
				_arrow._bShoot = true;		//ȭ�� �߻�
				_arrow._chargeTime = 0.0f;	//ȭ�� ���� �ð��� �ʱ�ȭ.
				_frameIndex = 0;			//frameIndex�� 0���� �ʱ�ȭ.
			}
			else
			{
				//ȭ������
				_arrow._chargeTime += 0.1f;
			}
		}
	}


	//ȭ���� ���ư��� ȭ���� ��ǥ �̵�
	if (_arrow._bShoot == true)
	{
		_arrow._point.x += cosf(PI / 2) * 2 + _arrow._speed;
		_arrow._point.y += -sinf(PI / 2) * 2;
		_arrow._speed += 2.1f;
	}

	//ȭ���浹
	//RECT temp;
	//if (IntersectRect(&temp, &_mainplayer->getenemyRect(), &_arrow))
	//{
	//	_arrowIs = false;
	//}
}

void subplayer::render()
{
	Rectangle(getMemDC(), _subPlayer.rc);

	switch (_state)
	{
	case pIDLE:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subIdle")->frameRender(getMemDC(), _subPlayer.rc.left - 10, _subPlayer.rc.top - 30);
		}
		else
		{
			IMAGEMANAGER->findImage("subIdle")->
				scaleFrameRender(getMemDC(), _subPlayer.rc.left - 10, _subPlayer.rc.top - 30, 
					_subPlayer.idle->getFrameX(), _subPlayer.idle->getFrameY(), -1.0F);
		}
		break;
	case pWALK:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subWalk")->frameRender(getMemDC(), _subPlayer.rc.left - 20, _subPlayer.rc.top - 30);
		}
		else
		{
			IMAGEMANAGER->findImage("subWalk")->
				scaleFrameRender(getMemDC(), _subPlayer.rc.left - 20, _subPlayer.rc.top - 30,
					_subPlayer.walk->getFrameX(), _subPlayer.walk->getFrameY(), -1.0F);
		}
		break;
	case pATTACK:
		if (_melee)
		{
			if (_subPlayer.sight)
			{
				IMAGEMANAGER->findImage("subMelee")->frameRender(getMemDC(), _subPlayer.rc.left - 10, _subPlayer.rc.top - 30);
			}
			else
			{
				IMAGEMANAGER->findImage("subMelee")->
					scaleFrameRender(getMemDC(), _subPlayer.rc.left - 10, _subPlayer.rc.top - 30,
						_subPlayer.atkmelee->getFrameX(), _subPlayer.atkmelee->getFrameY(), -1.0F);
			}
		}
		else
		{
			if (_subPlayer.sight)
			{
				IMAGEMANAGER->findImage("subShot")->frameRender(getMemDC(), _subPlayer.rc.left - 10, _subPlayer.rc.top - 30);
			}
			else
			{
				IMAGEMANAGER->findImage("subShot")->
					scaleFrameRender(getMemDC(), _subPlayer.rc.left - 10, _subPlayer.rc.top - 30,
						_subPlayer.atkshot->getFrameX(), _subPlayer.atkshot->getFrameY(), -1.0F);
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
			IMAGEMANAGER->findImage("subRun")->
				scaleFrameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top,
					_subPlayer.run->getFrameX(), _subPlayer.run->getFrameY(), -1.0F);
		}
		break;
	}
	
	if (_arrow._bShoot)
	{
		IMAGEMANAGER->findImage("arrow")->render(getMemDC(), _arrow._point.x, _arrow._point.y);
	}

	char chr[100];
	sprintf(chr, "�Ÿ� : %f", _distance);
	TextOut(getMemDC(), 100, 150, chr, strlen(chr));

	char chr1[100];
	sprintf(chr1, "ȭ�������ð� : %f", _arrow._chargeTime);
	TextOut(getMemDC(), 100, 200, chr1, strlen(chr1));
}

void subplayer::animation()
{
	switch (_state)
	{
	case pIDLE:				  //������
	{
		_frameCount++;
		_subPlayer.idle->setFrameY(0);
		if (_frameCount % 8 == 0)
		{
			_frameIndex++;
			if (_frameIndex > 2)
			{
				_frameIndex = 0;
			}
			_subPlayer.idle->setFrameX(_frameIndex);
		}
		break;
	}
	case pWALK:		//�ȱ�
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
		break;
	}
	case pATTACK:
		if (_melee)	//���� ������ �� ��
		{
			_frameCount++;
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
					_state = pIDLE;		//�����·� ��ȯ
				}
				_subPlayer.atkmelee->setFrameX(_frameIndex);
			}
		}
		else	//���Ÿ� ������ �� ��
		{
			_frameCount++;
			_subPlayer.atkshot->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 8)
					//���Ÿ� ������ �̹��� �������� 8��
					//���� _frameIndex�� 7���� ū ���� ������ ���� ������ �Ǵ��Ѵ�.
				{
					_frameCount = 0;	//_frameCount�� 0���� �ʱ�ȭ
					_frameIndex = 0;	//_frameIndex�� 0���� �ʱ�ȭ
					_state = pIDLE;		//�����·� ��ȯ
				}
				_subPlayer.atkshot->setFrameX(_frameIndex);
			}
		}
		break;
	case pRUN:
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
		break;
	}
	}
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
	}
}
