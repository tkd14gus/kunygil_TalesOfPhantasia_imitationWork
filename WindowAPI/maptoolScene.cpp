#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	//타일맵 이미지 초기화
	//IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 600, 800);
	_rcPalette = RectMakeCenter((_rcScreen.left + _rcScreen.right) / 2, _rcScreen.bottom - 192, 576, 288);
	_editMode = false;
	_editMoveDirect = false;
	_setSaveLoad = false;
	_slideTool = true;
	//맵툴세팅
	this->maptoolSetup();
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(48 * j, 48 * i, 48, 48);
		}
	}
	_palettePage = 1;
	sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
	//현재타일 초기화 (지형 = 잔디)
	_currentTile.x = 3;
	_currentTile.y = 0;

	_layer[0] = true;
	_layer[1] = false;
	_layer[2] = false;
	loadMapData(_dataName);
	return S_OK;
}

void maptoolScene::release()
{
}

void maptoolScene::update()
{
	if (_editMode)
	{
		if (INPUT->GetKeyDown(VK_D)) 
		{
			_editMode = false; 
			saveMapData(_dataName);
		}
		if (INPUT->GetKeyDown(0x31))
		{
			_editMoveDirect = false;
		}
		if (INPUT->GetKeyDown(0x32))
		{
			_editMoveDirect = true;
		}
	}
	else if (_setSaveLoad == true) // 세이브 확인창이 켜졌을때
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (!PtInRect(&_rcSaveWindow, _ptMouse)) // 세이브 확인창 밖을 클릭하면 세이브창 닫기
			{
				_setSaveLoad = false;
				return;
			}
			else if (PtInRect(&_rcSaveSlot[0], _ptMouse)) { sprintf_s(_fileName, "save1.mapsave"); }	//슬롯1번선택
			else if (PtInRect(&_rcSaveSlot[1], _ptMouse)) { sprintf_s(_fileName, "save2.mapsave"); }	//슬롯2번선택
			else if (PtInRect(&_rcSaveSlot[2], _ptMouse)) { sprintf_s(_fileName, "save3.mapsave"); }	//슬롯3번선택
			else if (PtInRect(&_rcSave, _ptMouse))
			{
				this->save(_fileName);
				_setSaveLoad = false;
				return;
			}
			//세이브완료
			else if (PtInRect(&_rcLoad, _ptMouse))
			{
				this->load(_fileName);
				_setSaveLoad = false;
				return;
			}
			//로드완료
		}
	}
	else
	{
		//#====================================================================================================
		//#				※※※ 필독 ※※※ 사용 방법
		//#				에디터를 사용하기 전에 칠한 타일은 에디터를 사용하더라도 데이터 변경 X
		//#				추후에 적용 되도록 작업할 예정이며
		//#				그 전에 에디터 맵 저장하면 인게임에서 난리납니다
		//#=====================================================================================================

		if (INPUT->GetKeyDown(VK_D)) { _editMode = true; }	//샘플타일 데이터 에디트 

		this->maptoolSetup();

		if (_rcPalette.top > WINSIZEY) // 최소화시 화면밖으로 나가면서 이하만큼남앗을때 버튼생성(이동) ※맵툴 셋업보다 밑에있어야함
		{
			_rcSaveLoad = RectMake(_rcPalette.left, WINSIZEY - 48, 96, 48);							//맵툴 UI
			_rcDummy1 = RectMake(_rcPalette.left + 96, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcDummy2 = RectMake(_rcPalette.left + 96 * 2, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcDummy3 = RectMake(_rcPalette.left + 96 * 3, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcslide = RectMake(_rcPalette.left + 96 * 4, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcArrow[0] = RectMake(_rcPalette.left + 96 * 5, WINSIZEY - 48, 48, 48);					//맵툴 UI			   왠지 수정의예감
			_rcArrow[1] = RectMake(_rcPalette.left + 96 * 5.5f, WINSIZEY - 48, 48, 48);					//맵툴 UI			   왠지 수정의예감
		}

		if (_slideTool == false && _rcPalette.top < WINSIZEY+17) // 최소화시=>화면밖까지 내리기 (맨위에 일정이상 내려갔을시 버튼이동하는 이프문있음)
		{
			_rcPalette.top += 5;
			_rcPalette.bottom += 5;
		}
		else if (_slideTool == true && _rcPalette.top > _rcScreen.bottom - 336) //최대화시=>초기위치까지 올리기 (336은 초기위치)
		{
			_rcPalette.top -= 5;
			_rcPalette.bottom -= 5;
		}

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
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rcSaveLoad, _ptMouse))
			{
				_setSaveLoad = true;
				//_ctrlSelect = CTRL_SAVE;  
				//this->save();


				//_ctrlSelect = CTRL_LOAD;
				//this->load();
			}
			if (PtInRect(&_rcDummy1, _ptMouse))
			{

			}
			if (PtInRect(&_rcDummy2, _ptMouse))
			{
				//_ctrlSelect = CTRL_TERRAIN;
			}
			if (PtInRect(&_rcDummy3, _ptMouse))
			{
				//_ctrlSelect = CTRL_OBJECT;
			}
			if (PtInRect(&_rcslide, _ptMouse))
			{
				if (_slideTool == false) { _slideTool = true; }
				else if (_slideTool == true ) { _slideTool = false; }
			}
			if (PtInRect(&_rcArrow[0], _ptMouse) && _palettePage > 1)
			{
				_palettePage--;
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);
			}
			if (PtInRect(&_rcArrow[1], _ptMouse) && _palettePage < 3)
			{
				_palettePage++;
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);
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
				//이미지 추가되면 #FF00FF 사각형으로 칠해버릴 예정 (#FF00FF는 마젠타색)
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
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1 && _tiles[i].imagePage[1] == -1)
				//하단 레이어에 그림이 없을 때 빈 사각형을 그려준다.
				//이미지 추가되면 #FF00FF 사각형으로 칠해버릴 예정 (#FF00FF는 마젠타색)
			{
				Rectangle(getMemDC(), _tiles[i].rc);
			}
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
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1 && _tiles[i].imagePage[1] == -1 && _tiles[i].imagePage[2] == -1)
				//하단 레이어에 그림이 없을 때 빈 사각형을 그려준다.
				//이미지 추가되면 #FF00FF 사각형으로 칠해버릴 예정 (#FF00FF는 마젠타색)
			{
				Rectangle(getMemDC(), _tiles[i].rc);
			}
			else
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2], 3.0f);
			}
		}
		else { continue; }
	}

	
	Rectangle(getMemDC(), _rcPalette);

	for (int i = 0; i < 60; i++)
	{
		Rectangle(getMemDC(), _sampleTile[i].rc);

		//하단의 샘플타일 랜더 스케일랜더로 16->48픽셀로 확대

		_sampleTile[i].tileFrameX = i % 10;
		_sampleTile[i].tileFrameY = i / 10;
		_sampleTile[i].imagePage = _palettePage;
		if (_sampleTile[i].canMove == true) { sprintf_s(_editModechar, "%d", 1); }
		else { sprintf_s(_editModechar, "%d", 0); }
		IMAGEMANAGER->findImage("map1")->scaleFrameRender(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top,i%10,i/10,3.0f);

		if (_editMode == true)
		{
			TextOut(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, _editModechar, strlen(_editModechar));
		}
	}

	Rectangle(getMemDC(), _rcSaveLoad);
	Rectangle(getMemDC(), _rcDummy1);
	Rectangle(getMemDC(), _rcDummy2);
	Rectangle(getMemDC(), _rcDummy3);
	Rectangle(getMemDC(), _rcslide);

	if (_palettePage > 1) { IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	if (_palettePage < 3) { IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }
	
	if (_setSaveLoad == true)
	{
		Rectangle(getMemDC(), _rcSaveWindow);
		Rectangle(getMemDC(), _rcSaveSlot[0]);
		Rectangle(getMemDC(), _rcSaveSlot[1]);
		Rectangle(getMemDC(), _rcSaveSlot[2]);	
		Rectangle(getMemDC(), _rcSave);
		Rectangle(getMemDC(), _rcLoad);

		frameBoxRender(_rcSaveWindow, 1.0f); //함수 확인용
	}
	frameBoxRender(_rcPalette, 1.0f);
}

void maptoolScene::maptoolSetup()
{
	//_rcPalette = RectMakeCenter((_rcScreen.left + _rcScreen.right) / 2, _rcScreen.bottom - 192, 576, 288);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_sampleTile[i * 10 + j].rc = RectMake(_rcPalette.left + (j * 48), _rcPalette.top + (i * 48), 48, 48);
			_sampleTile[i * 10 + j].tileFrameX = j;
			_sampleTile[i * 10 + j].tileFrameY = i;
		}
	}

	_rcSaveLoad = RectMake(_rcPalette.left + 480, _rcPalette.top, 96, 48);							//맵툴 UI
	_rcDummy1 = RectMake(_rcPalette.left + 480, _rcPalette.top + 48, 96, 48);						//맵툴 UI
	_rcDummy2 = RectMake(_rcPalette.left + 480, _rcPalette.top + 96, 96, 48);						//맵툴 UI
	_rcDummy3 = RectMake(_rcPalette.left + 480, _rcPalette.top + 144, 96, 48);						//맵툴 UI
	_rcslide = RectMake(_rcPalette.left + 480, _rcPalette.top + 192, 96, 48);						//맵툴 UI
	_rcArrow[0] = RectMake(_rcPalette.left + 480, _rcPalette.top + 240, 48, 48);					//맵툴 UI
	_rcArrow[1] = RectMake(_rcPalette.left + 528, _rcPalette.top + 240, 48, 48);					//맵툴 UI

	_rcSaveWindow = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2-50, 300, 250);					    //세이브로드UI
	for (int i = 0; i < 3; i++)																	    //세이브로드UI
	{																							    //세이브로드UI
		_rcSaveSlot[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 125 + i * 49, 250,50);		    //세이브로드UI
	}																							    //세이브로드UI
	_rcSave = RectMakeCenter(WINSIZEX/2-70,WINSIZEY/2+35,80,40);								    //세이브로드UI
	_rcLoad = RectMakeCenter(WINSIZEX/2+70,WINSIZEY/2+35,80,40);								    //세이브로드UI


	
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
					_tiles[i].imagePage[0] = _currentTile.pageNumber;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//현재버튼이 오브젝트냐?
				if (_layer[1])
				{
					_tiles[i].canMove[1] = _canMove;
					_tiles[i].tileFrameX[1] = _currentTile.x;
					_tiles[i].tileFrameY[1] = _currentTile.y;
					_tiles[i].imagePage[1] = _currentTile.pageNumber;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//현재버튼이 지우개냐?
				if (_layer[2])
				{
					_tiles[i].canMove[2] = _canMove;
					_tiles[i].tileFrameX[2] = _currentTile.x;
					_tiles[i].tileFrameY[2] = _currentTile.y;
					_tiles[i].imagePage[2] = _currentTile.pageNumber;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
			}
		}
	}
}

void maptoolScene::uiMove()
{

}

void maptoolScene::save(char* str)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(str , GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}
void maptoolScene::load(char* str)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(str, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void maptoolScene::saveMapData(char *str)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLETILEX * SAMPLETILEY, &write, NULL);
	CloseHandle(file);
}

void maptoolScene::loadMapData(char* str)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(str, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLETILEX * SAMPLETILEY, &read, NULL);
	CloseHandle(file);
}

void maptoolScene::editCanMove()
{

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				_sampleTile[i].canMove = !_sampleTile[i].canMove;
				break;
			}
		}
	}
}

void maptoolScene::frameBoxRender(int left, int top, int width, int height,float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), left, top, 0, 0, 17*scale, height , scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), left+ width - (17 * scale), top, 0, 0, 17 * scale, height, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), left, top, 0, 0, width, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), left, top+height-(17*scale), 0, 0, width, 17 * scale, scale);


	//프레임바디
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), left, top, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), left + width -(17*scale), top, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), left, top+height - (17*scale), scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), left + width - (17 * scale), top + height - (17 * scale), scale);
	//모서리

}
void maptoolScene::frameBoxRender(RECT rc, float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left-17 * scale, rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right, rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left, rc.top-17 * scale, 0, 0, rc.right - rc.left, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left,rc.bottom, 0, 0, rc.right - rc.left, 17 * scale, scale);


	//프레임바디
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left-17 * scale, rc.top-17 * scale, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right, rc.top-17 * scale, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left-17 * scale, rc.bottom , scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right, rc.bottom, scale);

	//모서리

}



//void maptoolScene::frameBoxRender(RECT rc, float scale)
//{
//	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
//	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
//	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, rc.right - rc.left, 17 * scale, scale);
//	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left, rc.top + rc.bottom - rc.top - (17 * scale), 0, 0, rc.right - rc.left, 17 * scale, scale);
//
//
//	//프레임바디
//	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left, rc.top, scale);
//	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, scale);
//	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left, rc.bottom - (17 * scale), scale);
//	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.bottom - (17 * scale), scale);
//	//모서리
//
//}  //렉트 내부에 그리는것 혹시쓸수도있어서 주석처리

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

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	TERRAIN t;
	t.x = frameX;
	t.y = frameY;

	return t;
}
