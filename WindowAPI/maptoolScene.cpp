#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	//타일맵 이미지 초기화
	//IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 600, 800);
	_tileSetting = false;
	//맵툴세팅
	this->maptoolSetup();

	//현재타일 초기화 (지형 = 잔디)
	_currentTile.x = 3;
	_currentTile.y = 0;

	_layer[0] = true;
	_layer[1] = false;
	_layer[2] = false;
	return S_OK;
}

void maptoolScene::release()
{
}

void maptoolScene::update()
{
	if (_tileSetting)
	{

	}
	else
	{
		if (INPUT->GetKeyDown(0x31)) { selectLayer1(); }
		if (INPUT->GetKeyDown(0x32)) { selectLayer2(); }
		if (INPUT->GetKeyDown(0x33)) { selectLayer3(); }

		if (INPUT->GetKey(VK_UP))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top--;
				_tiles[i].rc.bottom--;
			}
		}
		if (INPUT->GetKey(VK_DOWN))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top++;
				_tiles[i].rc.bottom++;
			}
		}
		if (INPUT->GetKey(VK_RIGHT))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left++;
				_tiles[i].rc.right++;
			}
		}
		if (INPUT->GetKey(VK_LEFT))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left--;
				_tiles[i].rc.right--;
			}
		}


		if (INPUT->GetKey(VK_LBUTTON)) this->setMap();
	}
}

void maptoolScene::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1)
				//하단 레이어에 그림이 없을 때 빈 사각형을 그려준다.
				//이미지 추가되면 #FF00FF 사각형으로 칠해버릴 예정
			{
				Rectangle(getMemDC(), _tiles[i].rc);
			}
			else
			{

			}
		}
		else { continue; }
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[1] == -1)
				//하단 레이어에 그림이 없을 때 빈 사각형을 그려준다.
				//이미지 추가되면 #FF00FF 사각형으로 칠해버릴 예정
			{
				Rectangle(getMemDC(), _tiles[i].rc);
			}
			else
			{

			}
		}
		else { continue; }
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[2] == -1)
				//하단 레이어에 그림이 없을 때 빈 사각형을 그려준다.
				//이미지 추가되면 #FF00FF 사각형으로 칠해버릴 예정
			{
				Rectangle(getMemDC(), _tiles[i].rc);
			}
			else
			{

			}
		}
		else { continue; }
	}


	Rectangle(getMemDC(), _rcPalette);
	for (int i = 0; i < 60; i++)
	{
		Rectangle(getMemDC(), _sampleTile[i].rc);
	}
	Rectangle(getMemDC(), _rcSave);
	Rectangle(getMemDC(), _rcLoad);
	Rectangle(getMemDC(), _rcTerrain);
	Rectangle(getMemDC(), _rcObject);
	Rectangle(getMemDC(), _rcEraser);
	if (_layer[0]) { IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	if (_layer[1]) { IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }
	if (_layer[2])
	{
		IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top);
		IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top);
	}
}
void maptoolScene::maptoolSetup()
{
	_rcPalette = RectMakeCenter((_rcScreen.left + _rcScreen.right) / 2, _rcScreen.bottom - 192, 576, 288);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_sampleTile[i * 10 + j].rc = RectMake(_rcPalette.left + (j * 48), _rcPalette.top + (i * 48), 48, 48);
			_sampleTile[i * 10 + j].tileFrameX = j;
			_sampleTile[i * 10 + j].tileFrameY = i;
		}
	}

	_rcSave = RectMake(_rcPalette.left + 480, _rcPalette.top, 96, 48);
	_rcLoad = RectMake(_rcPalette.left + 480, _rcPalette.top + 48, 96, 48);
	_rcTerrain = RectMake(_rcPalette.left + 480, _rcPalette.top + 96, 96, 48);
	_rcObject = RectMake(_rcPalette.left + 480, _rcPalette.top + 144, 96, 48);
	_rcEraser = RectMake(_rcPalette.left + 480, _rcPalette.top + 192, 96, 48);
	_rcArrow[0] = RectMake(_rcPalette.left + 480, _rcPalette.top + 240, 48, 48);
	_rcArrow[1] = RectMake(_rcPalette.left + 528, _rcPalette.top + 240, 48, 48);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(48 * j, 48 * i, TILESIZEX, TILESIZEY);
		}
	}
}

void maptoolScene::setMap()
{
	if (PtInRect(&_rcPalette, _ptMouse))
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTile[i].rc, _ptMouse))
			{
				_currentTile.pageNumber = _palettePage;
				_currentTile.x = _sampleTile[i].tileFrameX;
				_currentTile.y = _sampleTile[i].tileFrameY;
				_canMove = _sampleTile[i].canMove;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&_tiles[i].rc, _ptMouse))
			{
				if (_layer[0])
				{
					_tiles[i].canMove[0] = _canMove;
					_tiles[i].tileFrameX[0] = _currentTile.x;
					_tiles[i].tileFrameY[0] = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y, _currentTile.pageNumber);
				}
				//현재버튼이 오브젝트냐?
				if (_layer[1])
				{
					_tiles[i].canMove[1] = _canMove;
					_tiles[i].tileFrameX[1] = _currentTile.x;
					_tiles[i].tileFrameY[1] = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y, _currentTile.pageNumber);
				}
				//현재버튼이 지우개냐?
				if (_layer[2])
				{
					_tiles[i].canMove[2] = _canMove;
					_tiles[i].tileFrameX[2] = _currentTile.x;
					_tiles[i].tileFrameY[2] = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y, _currentTile.pageNumber);
				}
			}
		}
	}

}

void maptoolScene::uiMove()
{

}

void maptoolScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	/*
	while(true)
	{
		sprintf_s(str, "map%d.map"
	}
	*/
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

void maptoolScene::selectLayer1()
{
	_layer[0] = true;
	_layer[1] = false;
	_layer[2] = false;
}

void maptoolScene::selectLayer2()
{
	_layer[0] = false;
	_layer[1] = true;
	_layer[2] = false;
}

void maptoolScene::selectLayer3()
{
	_layer[0] = false;
	_layer[1] = false;
	_layer[2] = true;
}

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY, int page)
{
	TERRAIN t;
	t.x = frameX;
	t.y = frameY;
	t._palettePage = page;

	return t;
}
