#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{

	//ó���� ����â�� Ű�� ���� �����̴�.
	_isStateWinOpen = false;

	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = new player;
	_player->init();
	_subPlayer = new subplayer;
	_subPlayer->init();
	//���� ó�� ������ �� ���� ��ġ�� village(����)
	_mapLocation = 0;

	//ī�޶�� �׻� �߾��� ��ġ�� �־�� �Ѵ�.
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	//���� �ҷ��� �������ش�.
	this->mapSetting(_mapLocation);
	//Ÿ���� �÷��̾� ��ġ�� �°� �������ش�.
	this->tileSetting();

	//���� PLAYERDATA->getPlayerData()�� NULL�� �ƴ� ��
	//(���� ���� ������ NULL�� �ʱ�ȭ��)
	//_player�� �־��ش�.
	if (PLAYERDATA->getPlayerData() != NULL)
	{
		_player = PLAYERDATA->getPlayerData();
	}
	//���� PLAYERDATA->getTilesRC()[0].left�� 0�̶��
	//��Ʋ������ �̵��� ���� ���ٴ� ���̴�.
	//��, ��Ʈ�� �̵��� �������Ƿ� ���� �����͸� ������ �ʿ� ����.
	if (PLAYERDATA->getTilesRC()[0].left != 0)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc = PLAYERDATA->getTilesRC()[i];
		}
	}

	//state��Ʈ ��ġ�� �°� �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
			_stateRC[i] = RectMake(300 * i, 145, 300, 250);
		else
			_stateRC[i] = RectMake(300 * (i % 2), 405, 300, 250);
	}

	return S_OK;
}

void inGameScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
}

void inGameScene::update()
{
	//����â�� ������ ���� ���¶��.
	if (!_isStateWinOpen)
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
			//�ʵ��϶�
			if (_mapLocation == 1)
			{
				//�������� ��Ʋ������ �ٲܰ��� Ȯ�����ش�.
				this->changeBattleScene();
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
			//�ʵ��϶�
			if (_mapLocation == 1)
			{
				//�������� ��Ʋ������ �ٲܰ��� Ȯ�����ش�.
				this->changeBattleScene();
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
			//�ʵ��϶�
			if (_mapLocation == 1)
			{
				//�������� ��Ʋ������ �ٲܰ��� Ȯ�����ش�.
				this->changeBattleScene();
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
			//�ʵ��϶�
			if (_mapLocation == 1)
			{
				//�������� ��Ʋ������ �ٲܰ��� Ȯ�����ش�.
				this->changeBattleScene();
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

		//SŰ�� ������ ����â�� ���.
		//�ѹ��� Ȯ�����ٰŴϱ� GetKeyDown���� ���ش�.
		if (INPUT->GetKeyDown('S'))
		{
			//����â�� ����.
			_isStateWinOpen = true;
			//����â���� ��� �ɾ�� �ϴϱ� ���¸� �ȱ�� �ٲ��ش�.
			_player->setPlayerState(pWALK);
			//���� �� ���� �ٶ󺸰� �ִ� �������� ���Ŵϱ� ���� �ٶ󺸴� ������ �����Ѵ�.
			_saveDirect = _player->getDirect();
			//����â���� ó�� ���� �� ������ �Ʒ� �� 1�̴�.
			_player->setDirect(1);
		}
	}
	//����â�� ���ȴٸ�
	else
	{
		//SŰ�� �ٽ� ������ ��������.
		//�ѹ��� Ȯ�����ٰŴϱ� GetKeyDown���� ���ش�.
		if (INPUT->GetKeyDown('S'))
		{
			//����â�� ����.
			_isStateWinOpen = false;
			//�����ڸ��� ���´� IDLE�̴�.
			_player->setPlayerState(pIDLE);
			//�÷��̾ �ٶ� ������ �ٽ� �����ش�.
			_player->setDirect(_saveDirect);
		}
	}

}

void inGameScene::render()
{
	//����â�� �������� �ʴٸ�
	if (!_isStateWinOpen)
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
	//����â�� �����ִٸ�
	else
	{
		//�ϴ� ����â ���ȭ���� �����ְ�
		IMAGEMANAGER->render("stateWindow", getMemDC());

		//��ġ Ȯ�ο� ��Ʈ
		//for (int i = 0; i < 4; i++)
		//{
		//	Rectangle(getMemDC(), _stateRC[i]);
		//}
		//�÷��̾��� �̹����� �ȴ°� ������Ʈ
		_player->spinPlayer();
		//���� ������Ʈ�� ������� �̹��� ���
		IMAGEMANAGER->scaleFrameRender("cress", getMemDC(), _stateRC[0].right - 50, _stateRC[0].top + 20, IMAGEMANAGER->findImage("cress")->getFrameX(), IMAGEMANAGER->findImage("cress")->getFrameY(), 0.5f);

		//���� ĳ������ �̹����� �ȴ� ��� ������Ʈ
		_subPlayer->walkingInfo();
		//���� ������Ʈ�� ������� �̹��� ���
		IMAGEMANAGER->findImage("chester")->scaleFrameRender(getMemDC(), _stateRC[1].right - 50, _stateRC[1].top + 20,
			IMAGEMANAGER->findImage("chester")->getFrameX(), IMAGEMANAGER->findImage("chester")->getFrameY(), 1.0f);

		//TEXT�� ���� �ٲ��ش�.
		//�Ͼ��
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		//���� ���
		sprintf(_stateWin, "LV : %d", _player->getPlayer()->lv);
		TextOut(getMemDC(), _stateRC[0].left + 20, _stateRC[0].top + 50, _stateWin, strlen(_stateWin));
		sprintf(_stateWin, "LV : %d", _subPlayer->getSubPlayer()->lv);
		TextOut(getMemDC(), _stateRC[1].left + 20, _stateRC[1].top + 50, _stateWin, strlen(_stateWin));
		//�ִ� HP�� ���� HP���
		//Y�ุ �����ͺ��� 30 ��������
		sprintf(_stateWin, "HP : %d / %d", _player->getPlayer()->hp, _player->getPlayer()->maxHp);
		TextOut(getMemDC(), _stateRC[0].left + 20, _stateRC[0].top + 80, _stateWin, strlen(_stateWin));
		sprintf(_stateWin, "HP : %d / %d", _subPlayer->getSubPlayer()->hp, _subPlayer->getSubPlayer()->maxHp);
		TextOut(getMemDC(), _stateRC[1].left + 20, _stateRC[1].top + 80, _stateWin, strlen(_stateWin));
		//�ִ� TP�� ���� TP���
		//Y�ุ �����ͺ��� 30 ��������
		sprintf(_stateWin, "TP : %d / %d", _player->getPlayer()->tp, _player->getPlayer()->maxTp);
		TextOut(getMemDC(), _stateRC[0].left + 20, _stateRC[0].top + 110, _stateWin, strlen(_stateWin));
		sprintf(_stateWin, "TP: %d / %d", _subPlayer->getSubPlayer()->tp, _subPlayer->getSubPlayer()->maxTp);
		TextOut(getMemDC(), _stateRC[1].left + 20, _stateRC[1].top + 110, _stateWin, strlen(_stateWin));
		//�ٽ� ���������� �ٲ�����
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	}
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

void inGameScene::changeBattleScene()
{
	//���� �������� �ϼ� �� �Ǿ� �־ �ϴ� �ּ�ó��
	//int ran = RANDOM->Range(500);
	//
	//if(ran % 500 == 0)
	//{
	//	SCENEMANAGER->loadScene("����ȭ��");
	//	//�÷��̾� ������ �������ش�.
	//	PLAYERDATA->setPlayerData(_player);
	//	//Ÿ���� ��Ʈ ��ġ ����
	//	PLAYERDATA->setTilesRC(_tiles)
	//}
}
