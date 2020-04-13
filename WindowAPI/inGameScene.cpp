#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{

	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = new player;
	_player->init();
	
	//���� ó�� ������ �� ���� ��ġ�� village(����)
	_mapLocation = 0;

	//ī�޶�� �׻� �߾��� ��ġ�� �־�� �Ѵ�.
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	//���� �ҷ��� �������ش�.
	this->mapSetting(_mapLocation);
	//Ÿ���� �÷��̾� ��ġ�� �°� �������ش�.
	this->tileSetting();


	return S_OK;
}

void inGameScene::release()
{
	//_player->release();
	//SAFE_DELETE(_player);
}

void inGameScene::update()
{

	//�ΰ��ӿ��� ����Ű�� �����ٸ� Ÿ�ϵ鵵 ���� �������ش�.
	if (INPUT->GetKey(VK_UP))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.top++;
			_tiles[i].rc.bottom++;
			//���� �÷��̾��� Y��ǥ�� WINSIZEY / 2���� ���� ������ ���̻� �ö󰡸� �ȵȴ�.
			//�װ� ������༭ Ÿ���� �������� �����Ѵ�.
			//�Ʒ��� ��� Ÿ���� �������� �����ϴ� if���� ���� �����̴�.
			if (_player->getPlayerY() <= WINSIZEY / 2)
			{
				_tiles[i].rc.top--;
				_tiles[i].rc.bottom--;
			}
			//���� �÷��̾��� Y��ǥ�� (48 * 150 - WINSIZEY / 2)�Ʒ��� ������ Ÿ���� �����̸� �ȵǱ� ������ 1�� ���ش�.
			if (_player->getPlayerY() >= (48 * 150 - WINSIZEY / 2))
			{
				_tiles[i].rc.top--;
				_tiles[i].rc.bottom--;
			}
		}
	}
	//�ΰ��ӿ��� ����Ű�� �����ٸ� Ÿ�ϵ鵵 ���� �������ش�.
	if (INPUT->GetKey(VK_DOWN))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.top--;
			_tiles[i].rc.bottom--;
			//���� �÷��̾��� Y��ǥ�� WINSIZEY / 2���� ���� ������ Ÿ���� �����̸� �ȵǱ� ������ 1�� �����ش�.
			if (_player->getPlayerY() <= WINSIZEY / 2)
			{
				_tiles[i].rc.top++;
				_tiles[i].rc.bottom++;
			}
			//���� �÷��̾��� Y��ǥ�� (48 * 150 - WINSIZEY / 2)�̻��̸� ���̻� �ö󰡸� �ȵȴ�.
			if (_player->getPlayerY() >= (48 * 150 - WINSIZEY / 2))
			{
				_tiles[i].rc.top++;
				_tiles[i].rc.bottom++;
			}
		}
	}
	//�ΰ��ӿ��� ����Ű�� �����ٸ� Ÿ�ϵ鵵 ���� �������ش�.
	if (INPUT->GetKey(VK_RIGHT))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.left--;
			_tiles[i].rc.right--;
			//���� �÷��̾��� X��ǥ�� (48 * 120 - WINSIZEX / 2) - 40�̻��̸� ���̻� �̵��ϸ� �ȵȴ�.
			if (_player->getPlayerX() >= (48 * 120 - WINSIZEX / 2))
			{
				_tiles[i].rc.left++;
				_tiles[i].rc.right++;
			}
			//���� �÷��̾��� X��ǥ��  WINSIZEX / 2 - 40���� ���� ������ Ÿ���� �����̸� �ȵǱ� ������ 1�� �����ش�.
			if (_player->getPlayerX() <= WINSIZEX / 2)
			{
				_tiles[i].rc.left++;
				_tiles[i].rc.right++;
			}
		}
	}
	//�ΰ��ӿ��� ����Ű�� �����ٸ� Ÿ�ϵ鵵 ���� �������ش�.
	if (INPUT->GetKey(VK_LEFT))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.left++;
			_tiles[i].rc.right++;
			//���� �÷��̾��� X��ǥ��  WINSIZEX / 2 - 40���� ���� ������ Ÿ���� �����̸� �ȵǱ� ������ 1�� �����ش�.
			if (_player->getPlayerX() <= WINSIZEX / 2)
			{
				_tiles[i].rc.left--;
				_tiles[i].rc.right--;
			}
			//���� �÷��̾��� X��ǥ�� (48 * 120 - WINSIZEX / 2) - 40�̻��̸� ���̻� �̵��ϸ� �ȵȴ�.
			if (_player->getPlayerX() >= (48 * 120 - WINSIZEX / 2))
			{
				_tiles[i].rc.left--;
				_tiles[i].rc.right--;
			}
		}
	}

	_player->update();

	//���� ������ ��
	if (_mapLocation == 0)
	{
		//�÷��̾��� x�� ������ġ �̻����� ���������� �̵��Ѵٸ� �ʵ�� �̵�
		if (_player->getPlayerX() >= (48 * 120 - 32))
		{
			_mapLocation = 1;
			this->mapSetting(_mapLocation);
			//player��Ʈ�� ���̰� 64�̴� ������ 32���� ���� �� �ְ�,
			//Player��Ʈ�� ���̰� 128�̴� ������ 64���� ���� �� �ش�.
			_player->setPlayerRect(50, 80);
			//Ÿ���� �÷��̾� ��ġ�� �°� �������ش�.
			this->tileSetting();
		}
	}
	//���� �ʵ��� ��
	else if (_mapLocation == 1)
	{
		//�÷��̾��� x�� ������ġ �̻����� �������� �̵��Ѵٸ� ������ �̵�
		if (_player->getPlayerX() <= 32)
		{
			_mapLocation = 0;
			this->mapSetting(_mapLocation);
			//player��Ʈ�� ���̰� 64�̴� ������ 32���� ���� ���ؼ� ���� �����ʿ� ��������,
			//Player��Ʈ�� ���̰� 128�̴� ������ 64���� ���� �� �ش�.
			_player->setPlayerRect(48 * 120 - 50, 80);
			//Ÿ���� �÷��̾� ��ġ�� �°� �������ش�.
			this->tileSetting();
		}
	}

	//���� �浹�ϴ��� Ȯ���� ���� for��
	//�ȿ� ������ ���߿� ä������ ��
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rc, &_player->getPlayerDoorRc(), &_tiles[i].rc))
		{
			//���̾ƿ��� 3���̹Ƿ� 3�� �� �����ش�.
			for (int j = 0; j < 3; j++)
			{
				//���� ������, ������X, ������Y�� ��� "��"�̹����� ���ٸ�
				//������ �̹����� �ٲ��ִ� �ڵ带 ä������ ��
				if (_tiles[i].imagePage[j] == -1 && _tiles[i].tileFrameX[j] == -1 && _tiles[i].tileFrameY[j] == -1)
				{

				}
			}
		}
	} // end of for (int i = 0; i < TILEX * TILEY; i++)

	cout << _tiles[120 * 150 - 1].rc.right << " " << _tiles[120 * 150 - 1].rc.bottom << endl;
	cout << _player->getPlayer()->rc.right << " " << _player->getPlayer()->rc.bottom << endl;
}

void inGameScene::render()
{

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1)
				//�ϴ� ���̾ �׸��� ���� �� ���Ƿ� �������ش�.
			{
				Rectangle(getMemDC(), _tiles[i].rc);
			}
			else
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[0]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[0], _tiles[i].tileFrameY[0], 3.0f);
			}
		}
		else { continue; }
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1 && _tiles[i].imagePage[1] == -1) { continue; }
			else
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[1]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[1], _tiles[i].tileFrameY[1], 3.0f);
			}
		}
		else { continue; }
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1 && _tiles[i].imagePage[1] == -1 && _tiles[i].imagePage[2] == -1) { continue; }
			else
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2], 3.0f);
			}
		}
		else { continue; }
	}

	FrameRect(getMemDC(), _rcScreen, RGB(255, 0, 0));

	_player->render();
}

void inGameScene::mapSetting(int mapLocation)
{
	HANDLE file;
	DWORD read;

	if (mapLocation == 0)
		file = CreateFile("MapSave/save1.mapsave", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	else if (mapLocation == 1)
		file = CreateFile("MapSave/save2.mapsave", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	else
		file = CreateFile("MapSave/save3.mapsave", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void inGameScene::tileSetting()
{
	//�÷��̾ �ִ� ���� �߽����� Ÿ���� �Ű��ش�.
	for (int i = 0; i < TILEX * TILEY; i++)
	{

		//���� �÷��̾��� ��ġ��ŭ ������ �Ϸ��� _tiles[i].rc�� �������� �Ѵ�.
		//�� �� _tiles[i].rc�� �⺻ ��ġ�� �÷��̾ WINSIZEX / 2, WINSIZEY / 2�϶� �̹Ƿ� �� ��ġ���� �߽��� �� ��ǥ�� ���ָ�
		//�̵��� ���� ���´�.
		//�߰� - ���� Ÿ�ϵ��� ���� ������� 30, �������� 40��ŭ Ÿ���� �� �� ����. �װ����� �߰��� ������༭ Ÿ���� ��ġ ����
		//�׸�ŭ�� ���ָ� ���ϴ� ���� ���´�.
		//��� ����

		//���� y��ǥ�� WINSIZEY / 2���� ���� ��
		if (_player->getPlayerY() <= WINSIZEY / 2)
		{
			//top, bottom�� �������� ����
		}
		//���� y��ǥ�� (48 * 150 - WINSIZEY / 2)���� ũ�ٸ�
		else if (_player->getPlayerY() >= (48 * 150 - WINSIZEY / 2))
		{
			//(48 * 150 - WINSIZEY / 2)�� ȭ������� �� �������� Ÿ���� �� ������ ���̴�.
			//�� ��ġ�� ��ü HEIGHT���� WINSIZEY��ŭ �� ���� ����.
			//������ Ÿ���� top�� bottom���� ��ü ���̿��� WINSIZEY�� �� ����ŭ ���ָ�
			//���� �ϴ��� Ÿ���� ī�޶� ��Ʈ ������ ���´�.
			//x��ǥ ����
			_tiles[i].rc.top -= (48 * 150 - WINSIZEY);
			_tiles[i].rc.bottom -= (48 * 150 - WINSIZEY);
		}
		//���� y��ǥ��  WINSIZEY / 2���� ũ��, (48 * 150 - WINSIZEY / 2)���� �۴ٸ�
		else
		{
			//_tiles[i].rc�� �⺻ ��ġ�� �÷��̾ WINSIZEX / 2, WINSIZEY / 2�϶� �̹Ƿ� �� ��ġ���� �߽��� �� ��ǥ�� ���ָ�
			//�̵��� ���� ���´�.
			//�߰� - ���� Ÿ�ϵ��� ���� ������� 30, �������� 40��ŭ Ÿ���� �� �� ����. �װ����� �߰��� ������༭ Ÿ���� ��ġ ����
			//�׸�ŭ�� ���ָ� ���ϴ� ���� ���´�.
			//x��ǥ ����
			_tiles[i].rc.top -= (_player->getPlayerRc().top - (WINSIZEY / 2 - 64));
			_tiles[i].rc.bottom -= (_player->getPlayerRc().bottom - (WINSIZEY / 2 + 64));
		}

		//���� x��ǥ�� WINSIZEX / 2 ���� ���� ��
		if (_player->getPlayerX() <= WINSIZEX / 2)
		{
			//left, right�� �������� ����
		}
		//���� x��ǥ�� (48 * 120 - WINSIZEX / 2)���� ũ�ٸ�
		else if (_player->getPlayerX() >= (48 * 120 - WINSIZEX / 2))
		{
			_tiles[i].rc.left -= (48 * 120 - WINSIZEX);
			_tiles[i].rc.right -= (48 * 120 - WINSIZEX);
		}
		//���� x��ǥ��  WINSIZEX / 2���� ũ��, (48 * 120 - WINSIZEX / 2)���� �۴ٸ�
		else
		{
			_tiles[i].rc.left -= (_player->getPlayerRc().left - (WINSIZEX / 2 - 32));
			_tiles[i].rc.right -= (_player->getPlayerRc().right - (WINSIZEX / 2 + 32));
		}
	}
}
