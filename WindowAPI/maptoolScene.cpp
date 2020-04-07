#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	//Ÿ�ϸ� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);

	//��������
	this->maptoolSetup();

	//����Ÿ�� �ʱ�ȭ (���� = �ܵ�)
	_currentTile.x = 3;
	_currentTile.y = 0;

	//�����׸��� �Ӽ����� �����ϱ�
	_ctrlSelect = CTRL_TERRAIN;

	return S_OK;
}

void maptoolScene::release()
{
}

void maptoolScene::update()
{
	if (INPUT->GetKey(VK_LBUTTON)) this->setMap();
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcSave, _ptMouse))
		{
			_ctrlSelect = CTRL_SAVE;
			this->save();
		}
		if (PtInRect(&_rcLoad, _ptMouse))
		{
			_ctrlSelect = CTRL_LOAD;
			this->load();
		}
		if (PtInRect(&_rcTerrain, _ptMouse))
		{
			_ctrlSelect = CTRL_TERRAIN;
		}
		if (PtInRect(&_rcObject, _ptMouse))
		{
			_ctrlSelect = CTRL_OBJECT;
		}
		if (PtInRect(&_rcEraser, _ptMouse))
		{
			_ctrlSelect = CTRL_ERASER;
		}
	}
}

void maptoolScene::render()
{
	//Ÿ�ϸ� �̹��� ��üȭ�� ������ܿ� ��ġ�ϱ�
	IMAGEMANAGER->render("tilemap", getMemDC(), 660, 0);

	//�ΰ���ȭ�� ������ �׸���
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//�ΰ���ȭ�� ������Ʈ�� �׸���
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	//���� ����ȭ�� �� ������ ����Ÿ�� ��Ʈ �����ֱ�
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(getMemDC(), _tiles[i].rc);
			//FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 255, 0));
		}

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			//Rectangle(getMemDC(), _sampleTile[i].rc);
			FrameRect(getMemDC(), _sampleTile[i].rc, RGB(255, 255, 0));
		}
	}


	//��Ʈ�� ��ư ��Ʈ �����ֱ�
	Rectangle(getMemDC(), _rcSave);
	Rectangle(getMemDC(), _rcLoad);
	Rectangle(getMemDC(), _rcTerrain);
	Rectangle(getMemDC(), _rcObject);
	Rectangle(getMemDC(), _rcEraser);

	//��ư��Ʈ �ؽ�Ʈ �����ֱ�
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	TextOut(getMemDC(), _rcSave.left + 20, _rcSave.top + 20, "���̺�", strlen("���̺�"));
	TextOut(getMemDC(), _rcLoad.left + 20, _rcLoad.top + 20, "�ε�", strlen("�ε�"));
	TextOut(getMemDC(), _rcTerrain.left + 20, _rcTerrain.top + 20, "����", strlen("����"));
	TextOut(getMemDC(), _rcObject.left + 20, _rcObject.top + 20, "������Ʈ", strlen("������Ʈ"));
	TextOut(getMemDC(), _rcEraser.left + 20, _rcEraser.top + 20, "���찳", strlen("���찳"));

}

void maptoolScene::maptoolSetup()
{
	//���� �ΰ���ȭ�� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	//������ ����Ÿ�� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTile[i * SAMPLETILEX + j].rc = RectMake(660 + j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;
		}
	}

	//���� �ΰ���ȭ�� ��� �ܵ� �⺻Ÿ���� �ǵ��� �����ϱ�
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}
	//��Ʈ�� ��Ʈ ��ġ �ʱ�ȭ
	_rcSave = RectMake(660, 400, 100, 50);
	_rcLoad = RectMake(660 + 100, 400, 100, 50);
	_rcTerrain = RectMake(660, 400 + 100, 100, 50);
	_rcObject = RectMake(660 + 100, 400 + 100, 100, 50);
	_rcEraser = RectMake(660 + 200, 400 + 100, 100, 50);

}

void maptoolScene::setMap()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}

	//�ΰ���ȭ�� ��ƮƲ�� �浹�߳�?
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			//�����ư�� �����̳�?
			if (_ctrlSelect == CTRL_TERRAIN)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;
				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			//�����ư�� ������Ʈ��?
			if (_ctrlSelect == CTRL_OBJECT)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;
				_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
			}
			//�����ư�� ���찳��?
			if (_ctrlSelect == CTRL_ERASER)
			{
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
				_tiles[i].obj = OBJ_NONE;
			}
		}
	}

}

void maptoolScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}

void maptoolScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	//�ø�Ʈ
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	//��
	if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}
	//�ܵ�
	if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	//��
	if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	//��Ÿ
	return TR_GROUND;
}

OBJECT maptoolScene::objectSelect(int frameX, int frameY)
{
	return OBJ_BLOCKS;
}
