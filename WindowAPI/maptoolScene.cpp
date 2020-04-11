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
	_setSaveSlot = 3;
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
	_currentTile.pageNumber = _palettePage;
	_currentTile.x = 1;
	_currentTile.y = 3;

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
	if (_editMode)
	{
		if (INPUT->GetKeyDown(VK_D))
		{
			_editMode = false;
			sprintf(_dataName, "MapData/map%d.txt", _currentTile.pageNumber);
			saveMapData(_dataName);
		}
		if (INPUT->GetKeyDown(VK_1))
		{
			_editCanMove = true;
			_editMoveDirect = false;
		}
		if (INPUT->GetKeyDown(VK_2))
		{
			_editCanMove = false;
			_editMoveDirect = true;
		}
		
		if (_editCanMove)
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
		if (_editMoveDirect)
		{
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTile[i].rc, _ptMouse))
				{
					if (INPUT->GetKeyUp(VK_UP)) { _sampleTile[i].direct[0] = !_sampleTile[i].direct[0]; }
					if (INPUT->GetKeyUp(VK_DOWN)) { _sampleTile[i].direct[1] = !_sampleTile[i].direct[1]; }
					if (INPUT->GetKeyUp(VK_LEFT)) { _sampleTile[i].direct[2] = !_sampleTile [i].direct[2]; }
					if (INPUT->GetKeyUp(VK_RIGHT)) { _sampleTile[i].direct[3] = !_sampleTile[i].direct[3]; }
					break;
				}
			}
		}
	}
	else if (_setSaveLoad == true) // 세이브 확인창이 켜졌을때
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{

			if (PtInRect(&_rcSaveSlot[0], _ptMouse)) 
			{ _setSaveSlot = 0; }	//슬롯1번선택
			if (PtInRect(&_rcSaveSlot[1], _ptMouse)) 
			{ _setSaveSlot = 1; }	//슬롯2번선택
			if (PtInRect(&_rcSaveSlot[2], _ptMouse)) 
			{ _setSaveSlot = 2; }	//슬롯3번선택

			if (_setSaveSlot == 0) 
			{ sprintf_s(_mapName, "MapSave/save1.mapsave"); }	//슬롯1번파일으로 이름변경
			else if (_setSaveSlot == 1) { sprintf_s(_mapName, "MapSave/save2.mapsave"); }	//슬롯2번파일으로 이름변경
			else if (_setSaveSlot == 2) { sprintf_s(_mapName, "MapSave/save3.mapsave"); }	//슬롯3번파일으로 이름변경

		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (!PtInRect(&_rcSaveWindow, _ptMouse)) // 세이브 확인창 밖을 클릭하면 세이브창 닫기
			{
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			else if (PtInRect(&_rcSave, _ptMouse))
			{
				this->save(_mapName);
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			//세이브완료
			else if (PtInRect(&_rcLoad, _ptMouse))
			{
				this->load(_mapName);
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			//로드완료
		}
	}
	else
	{	
		_rcMouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 48, 48);

		//#====================================================================================================
		//#				※※※ 필독 ※※※ 사용 방법
		//#				에디터를 사용하기 전에 칠한 타일은 에디터를 사용하더라도 데이터 변경 X
		//#				추후에 적용 되도록 작업할 예정이며
		//#				그 전에 에디터 맵 저장하면 인게임에서 난리납니다
		//#=====================================================================================================
		if (INPUT->GetKeyDown(VK_D))
		{
			//샘플타일 데이터 에디트 
			loadMapData(_dataName);
			_editMode = true;
		}

		this->maptoolSetup();

		if (_rcPalette.top > WINSIZEY) // 최소화시 화면밖으로 나가면서 이하만큼남앗을때 버튼생성(이동) ※맵툴 셋업보다 밑에있어야함
		{
			_rcSaveLoad = RectMake(_rcPalette.left, WINSIZEY - 48, 96, 48);							//맵툴 UI
			_rcEraser = RectMake(_rcPalette.left + 96, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcDummy2 = RectMake(_rcPalette.left + 96 * 2, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcDummy3 = RectMake(_rcPalette.left + 96 * 3, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcslide = RectMake(_rcPalette.left + 96 * 4, WINSIZEY - 48, 96, 48);						//맵툴 UI
			_rcArrow[0] = RectMake(_rcPalette.left + 96 * 5, WINSIZEY - 48, 48, 48);					//맵툴 UI			   왠지 수정의예감
			_rcArrow[1] = RectMake(_rcPalette.left + 96 * 5.5f, WINSIZEY - 48, 48, 48);					//맵툴 UI			   왠지 수정의예감
		}

		if (_slideTool == false && _rcPalette.top < WINSIZEY + 17) // 최소화시=>화면밖까지 내리기 (맨위에 일정이상 내려갔을시 버튼이동하는 이프문있음)
		{
			_rcPalette.top += 5;
			_rcPalette.bottom += 5;
		}
		else if (_slideTool == true && _rcPalette.top > _rcScreen.bottom - 336) //최대화시=>초기위치까지 올리기 (336은 초기위치)
		{
			_rcPalette.top -= 5;
			_rcPalette.bottom -= 5;
		}

		//레이어 선택
		if (INPUT->GetKeyDown(VK_1)) { selectLayer1(); }
		if (INPUT->GetKeyDown(VK_2)) { selectLayer2(); }
		if (INPUT->GetKeyDown(VK_3)) { selectLayer3(); }

		//화면 이동
		
		if (INPUT->GetKey(VK_UP))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top += 10;
				_tiles[i].rc.bottom += 10;
			}
		}
		if (INPUT->GetKey(VK_DOWN))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top -= 10;
				_tiles[i].rc.bottom -= 10;
			}
		}
		if (INPUT->GetKey(VK_RIGHT))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left -= 10;
				_tiles[i].rc.right -= 10;
			}
		}
		if (INPUT->GetKey(VK_LEFT))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left += 10;
				_tiles[i].rc.right += 10;
			}
		}

		//포인터가 샘플타일 위에 있다면 샘플타일 선택
		//포인터가 맵타일 위에 있다면 선택되어 있는 샘플타일을 맵타일에 칠해준다.
		if (INPUT->GetKey(VK_LBUTTON)) this->setMap();
		//버튼 클릭 부분
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (PtInRect(&_rcSaveLoad, _ptMouse))
			{
				_setSaveLoad = true;
			}
			if (PtInRect(&_rcEraser, _ptMouse))
			{
				_currentTile.pageNumber = -1;
			}
			if (PtInRect(&_rcDummy2, _ptMouse))
			{
				
			}
			if (PtInRect(&_rcDummy3, _ptMouse))
			{
				
			}
			if (PtInRect(&_rcslide, _ptMouse))
			{
				if (_slideTool == false) { _slideTool = true; }
				else if (_slideTool == true) { _slideTool = false; }
			}
			if (PtInRect(&_rcArrow[0], _ptMouse) && _palettePage > 1)			//샘플타일의 번호가 1보다 클 때
			{																	
				_palettePage--;													//샘플타일의 번호를 1 감소시키고
				sprintf_s(_imageName, "map%d", _palettePage);					
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//해당 샘플타일을 팔레트에 그려준다.
			}
			if (PtInRect(&_rcArrow[1], _ptMouse) && _palettePage < 3)			//샘플타일의 번호가 최대값보다 작을 때
			{
				_palettePage++;													//샘플타일의 번호를 1 증가시키고
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//해당 샘플타일을 팔레트에 그려준다.
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
				//하단 레이어에 그림이 없을 때 임의로 설정해준다.
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
		RECT rc;
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

	
	Rectangle(getMemDC(), _rcPalette);

	//레이어 이미지 그리기
	if (_layer[0]) { IMAGEMANAGER->findImage("Layer")->frameRender(getMemDC(), _rcScreen.right - 128, _rcScreen.top, 0, 0); }
	else if (_layer[1]) { IMAGEMANAGER->findImage("Layer")->frameRender(getMemDC(), _rcScreen.right - 128, _rcScreen.top, 1, 0); }
	else { IMAGEMANAGER->findImage("Layer")->frameRender(getMemDC(), _rcScreen.right - 128, _rcScreen.top, 2, 0); }
	
	
	for (int i = 0; i < 60; i++)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		Rectangle(getMemDC(), _sampleTile[i].rc);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);

		//하단의 샘플타일 랜더 스케일랜더로 16->48픽셀로 확대

		_sampleTile[i].tileFrameX = i % 10;
		_sampleTile[i].tileFrameY = i / 10;
		_sampleTile[i].imagePage = _palettePage;


		IMAGEMANAGER->findImage("map1")->scaleFrameRender(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top,i%10,i/10,3.0f);

		if (_editMode && _editCanMove)
		{
			if (_sampleTile[i].canMove == true) { sprintf_s(_canMoveChar, "%d", 1); }
			else { sprintf_s(_canMoveChar, "%d", 0); }

			TextOut(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, _canMoveChar, strlen(_canMoveChar));
		}

		if (_editMode && _editMoveDirect)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_sampleTile[i].direct[j] == true) { _moveDirectChar[j] = 'T'; }
				else { _moveDirectChar[j] = 'F'; }
			}
			TextOut(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, _moveDirectChar, strlen(_moveDirectChar));
		}
	}

	IMAGEMANAGER->findImage("Eraser")->render(getMemDC(), _rcEraser.left, _rcEraser.top);			//지우개 이미지 출력

	Rectangle(getMemDC(), _rcDummy2);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	Rectangle(getMemDC(), _rcDummy3);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	Rectangle(getMemDC(), _rcslide);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.

	frameBoxRender(_rcPalette, 1.0f);


	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), _rcArrow[0].left, _rcArrow[0].top, _rcArrow[1].right, _rcArrow[1].bottom);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	//샘플타일의 번호가 1보다 작은 경우는 없으므로 1보다 큰 경우에만 이전 타일로 넘어가는 화살표를 보여준다.
	if (_palettePage > 1) { IMAGEMANAGER->findImage("activateLeft")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	else if (_palettePage == 1) { IMAGEMANAGER->findImage("Left")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	//샘플타일의 번호가 최대값보다 큰 경우는 없으므로 최대값보다 작은 경우에만 다음 타일로 넘어가는 화살표를 보여준다.
	if (_palettePage <= SMAPLETILECOUNT) { IMAGEMANAGER->findImage("activateRight")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }
	else { IMAGEMANAGER->findImage("Right")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }
	
	
	if (_setSaveLoad == true)
	{
		frameBoxRender(_rcSaveWindow, 1.0f); //세이브확인창프레임

		Rectangle(getMemDC(), _rcSaveWindow);
		IMAGEMANAGER->findImage("textbox")->render(getMemDC(), _rcSaveWindow.left, _rcSaveWindow.top, 0, 0, 
			_rcSaveWindow.right - _rcSaveWindow.left, _rcSaveWindow.bottom - _rcSaveWindow.top);

		//Rectangle(getMemDC(), _rcSaveSlot[0]);
		//Rectangle(getMemDC(), _rcSaveSlot[1]);
		//Rectangle(getMemDC(), _rcSaveSlot[2]);	

		for (int i = 0; i < SMAPLETILECOUNT; i++)
		{
			if (PtInRect(&_rcSaveSlot[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("activetextbox")->render(getMemDC(), _rcSaveSlot[i].left, _rcSaveSlot[i].top, 0, 0,
					_rcSaveSlot[i].right - _rcSaveSlot[i].left, _rcSaveSlot[i].bottom - _rcSaveSlot[i].top);
			}//마우스 가져가면 활성화

			if (_setSaveSlot == i)
			{
				IMAGEMANAGER->findImage("activetextbox")->render(getMemDC(), _rcSaveSlot[i].left, _rcSaveSlot[i].top, 0, 0,
					_rcSaveSlot[i].right - _rcSaveSlot[i].left, _rcSaveSlot[i].bottom - _rcSaveSlot[i].top);
			}
		}


		FrameRect(getMemDC(), _rcSaveSlot[0], RGB(255, 255, 255));				 //세이브슬롯 구분해주기
		FrameRect(getMemDC(), _rcSaveSlot[1], RGB(255, 255, 255));				 //세이브슬롯 구분해주기
		FrameRect(getMemDC(), _rcSaveSlot[2], RGB(255, 255, 255));				 //세이브슬롯 구분해주기

		Rectangle(getMemDC(), _rcSave);
		frameBoxRender(_rcSave, 0.3f);															//세이브 버튼 이미지..미안..
		IMAGEMANAGER->findImage("save")->render(getMemDC(), _rcSave.left-1, _rcSave.top-1);

		Rectangle(getMemDC(), _rcLoad);
		frameBoxRender(_rcLoad, 0.3f);															//로드 버튼 마찬가지로 이미지 지못미..
		IMAGEMANAGER->findImage("load")->render(getMemDC(), _rcLoad.left-1, _rcLoad.top-1);
	}
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
	_rcEraser = RectMake(_rcPalette.left + 480, _rcPalette.top + 48, 96, 48);						//맵툴 UI
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
	_rcSave = RectMakeCenter(WINSIZEX/2-70,WINSIZEY/2+35,80,35);								    //세이브로드UI
	_rcLoad = RectMakeCenter(WINSIZEX/2+70,WINSIZEY/2+35,80,35);								    //세이브로드UI

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
				//제일 아래쪽 레이어인가?
				if (_layer[0])
				{
					_tiles[i].canMove[0] = _canMove;
					_tiles[i].tileFrameX[0] = _currentTile.x;
					_tiles[i].tileFrameY[0] = _currentTile.y;
					_tiles[i].imagePage[0] = _currentTile.pageNumber;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//중간 레이어인가?
				if (_layer[1])
				{
					_tiles[i].canMove[1] = _canMove;
					_tiles[i].tileFrameX[1] = _currentTile.x;
					_tiles[i].tileFrameY[1] = _currentTile.y;
					_tiles[i].imagePage[1] = _currentTile.pageNumber;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//제일 위쪽의 레이어인가?
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

	file = CreateFile(str, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		file = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX-2) * SAMPLETILEY, &write, NULL);
	}
	else
	{
		WriteFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX - 2) * SAMPLETILEY, &write, NULL);
	}
	CloseHandle(file);
}

void maptoolScene::loadMapData(char* str)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(str, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		saveMapData(str);
	}
	else
	{
		ReadFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX - 2) * SAMPLETILEY, &read, NULL);
	}
	CloseHandle(file);
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
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left-17 * scale, rc.top-1, 0, 0, 17 * scale, rc.bottom+1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right, rc.top-1, 0, 0, 17 * scale, rc.bottom+1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left-1, rc.top-17 * scale, 0, 0, rc.right+1 - rc.left, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left-1,rc.bottom, 0, 0, rc.right+1 - rc.left, 17 * scale, scale);


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
