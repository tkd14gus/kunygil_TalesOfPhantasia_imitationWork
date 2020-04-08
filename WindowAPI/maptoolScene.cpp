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

	//지형그리기 속성으로 시작하기
	_ctrlSelect = CTRL_TERRAIN;

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
		IMAGEMANAGER->findImage("citytile")->scaleFrameRender(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top,i%10,i/10,3.0f);
	}


	Rectangle(getMemDC(), _rcSave);
	Rectangle(getMemDC(), _rcLoad);
	Rectangle(getMemDC(), _rcTerrain);
	Rectangle(getMemDC(), _rcObject);
	Rectangle(getMemDC(), _rcEraser);
	IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top);
	IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top);
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
	/*for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}*/

	//인게임화면 렉트틀과 충돌했냐?
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (PtInRect(&_tiles[i].rc, _ptMouse))
	//	{
	//		//현재버튼이 지형이냐?
	//		if (_ctrlSelect == CTRL_TERRAIN)
	//		{
	//			_tiles[i].terrainFrameX = _currentTile.x;
	//			_tiles[i].terrainFrameY = _currentTile.y;
	//			_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
	//		}
	//		//현재버튼이 오브젝트냐?
	//		if (_ctrlSelect == CTRL_OBJECT)
	//		{
	//			_tiles[i].objFrameX = _currentTile.x;
	//			_tiles[i].objFrameY = _currentTile.y;
	//			_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
	//		}
	//		//현재버튼이 지우개냐?
	//		if (_ctrlSelect == CTRL_ERASER)
	//		{
	//			_tiles[i].objFrameX = 0;
	//			_tiles[i].objFrameY = 0;
	//			_tiles[i].obj = OBJ_NONE;
	//		}
	//	}
	//}

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

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	//시멘트
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	//땅
	if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}
	//잔디
	if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	//물
	if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	//기타
	return TR_GROUND;
}

OBJECT maptoolScene::objectSelect(int frameX, int frameY)
{
	return OBJ_BLOCKS;
}
