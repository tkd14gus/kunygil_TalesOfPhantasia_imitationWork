#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	//Ÿ�ϸ� �̹��� �ʱ�ȭ
	//IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 600, 800);
	_rcPalette = RectMakeCenter((_rcScreen.left + _rcScreen.right) / 2, _rcScreen.bottom - 192, 576, 288);
	_editMode = false;
	_editMoveDirect = false;
	_setSaveLoad = false;
	_slideTool = true;
	_setSaveSlot = 3;
	//��������
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
	//����Ÿ�� �ʱ�ȭ (���� = �ܵ�)
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
		if (INPUT->GetKeyDown(VK_LBUTTON))
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
	else if (_setSaveLoad == true) // ���̺� Ȯ��â�� ��������
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{

			if (PtInRect(&_rcSaveSlot[0], _ptMouse)) 
			{ _setSaveSlot = 0; }	//����1������
			if (PtInRect(&_rcSaveSlot[1], _ptMouse)) 
			{ _setSaveSlot = 1; }	//����2������
			if (PtInRect(&_rcSaveSlot[2], _ptMouse)) 
			{ _setSaveSlot = 2; }	//����3������

			if (_setSaveSlot == 0) 
			{ sprintf_s(_mapName, "save1.mapsave"); }	//����1���������� �̸�����
			else if (_setSaveSlot == 1) { sprintf_s(_mapName, "save2.mapsave"); }	//����2���������� �̸�����
			else if (_setSaveSlot == 2) { sprintf_s(_mapName, "save3.mapsave"); }	//����3���������� �̸�����

		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (!PtInRect(&_rcSaveWindow, _ptMouse)) // ���̺� Ȯ��â ���� Ŭ���ϸ� ���̺�â �ݱ�
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
			//���̺�Ϸ�
			else if (PtInRect(&_rcLoad, _ptMouse))
			{
				this->load(_mapName);
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			//�ε�Ϸ�
		}
	}
		else
		{
			//#====================================================================================================
			//#				�ءء� �ʵ� �ءء� ��� ���
			//#				�����͸� ����ϱ� ���� ĥ�� Ÿ���� �����͸� ����ϴ��� ������ ���� X
			//#				���Ŀ� ���� �ǵ��� �۾��� �����̸�
			//#				�� ���� ������ �� �����ϸ� �ΰ��ӿ��� �������ϴ�
			//#=====================================================================================================

			if (INPUT->GetKeyDown(0x44)) { _editMode = true; }	//����Ÿ�� ������ ����Ʈ 

			this->maptoolSetup();

			if (_rcPalette.top > WINSIZEY) // �ּ�ȭ�� ȭ������� �����鼭 ���ϸ�ŭ�������� ��ư����(�̵�) �ظ��� �¾����� �ؿ��־����
			{
				_rcSaveLoad = RectMake(_rcPalette.left, WINSIZEY - 48, 96, 48);							//���� UI
				_rcDummy1 = RectMake(_rcPalette.left + 96, WINSIZEY - 48, 96, 48);						//���� UI
				_rcDummy2 = RectMake(_rcPalette.left + 96 * 2, WINSIZEY - 48, 96, 48);						//���� UI
				_rcDummy3 = RectMake(_rcPalette.left + 96 * 3, WINSIZEY - 48, 96, 48);						//���� UI
				_rcslide = RectMake(_rcPalette.left + 96 * 4, WINSIZEY - 48, 96, 48);						//���� UI
				_rcArrow[0] = RectMake(_rcPalette.left + 96 * 5, WINSIZEY - 48, 48, 48);					//���� UI			   ���� �����ǿ���
				_rcArrow[1] = RectMake(_rcPalette.left + 96 * 5.5f, WINSIZEY - 48, 48, 48);					//���� UI			   ���� �����ǿ���
			}

			if (_slideTool == false && _rcPalette.top < WINSIZEY + 17) // �ּ�ȭ��=>ȭ��۱��� ������ (������ �����̻� ���������� ��ư�̵��ϴ� ����������)
			{
				_rcPalette.top += 5;
				_rcPalette.bottom += 5;
			}
			else if (_slideTool == true && _rcPalette.top > _rcScreen.bottom - 336) //�ִ�ȭ��=>�ʱ���ġ���� �ø��� (336�� �ʱ���ġ)
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
			if (INPUT->GetKeyUp(VK_LBUTTON))
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
					else if (_slideTool == true) { _slideTool = false; }
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
				//�ϴ� ���̾ �׸��� ���� �� �� �簢���� �׷��ش�.
				//�̹��� �߰��Ǹ� #FF00FF �簢������ ĥ�ع��� ���� (#FF00FF�� ����Ÿ��)
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
				//�ϴ� ���̾ �׸��� ���� �� �� �簢���� �׷��ش�.
				//�̹��� �߰��Ǹ� #FF00FF �簢������ ĥ�ع��� ���� (#FF00FF�� ����Ÿ��)
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
				//�ϴ� ���̾ �׸��� ���� �� �� �簢���� �׷��ش�.
				//�̹��� �߰��Ǹ� #FF00FF �簢������ ĥ�ع��� ���� (#FF00FF�� ����Ÿ��)
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

		//�ϴ��� ����Ÿ�� ���� �����Ϸ����� 16->48�ȼ��� Ȯ��

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

	frameBoxRender(_rcPalette, 1.0f);

	if (_palettePage > 1) { IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	if (_palettePage < 3) { IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }

	
	if (_setSaveLoad == true)
	{
		frameBoxRender(_rcSaveWindow, 1.0f); //���̺�Ȯ��â������

		Rectangle(getMemDC(), _rcSaveWindow);
		IMAGEMANAGER->findImage("textbox")->render(getMemDC(), _rcSaveWindow.left, _rcSaveWindow.top, 0, 0, 
			_rcSaveWindow.right - _rcSaveWindow.left, _rcSaveWindow.bottom - _rcSaveWindow.top);

		//Rectangle(getMemDC(), _rcSaveSlot[0]);
		//Rectangle(getMemDC(), _rcSaveSlot[1]);
		//Rectangle(getMemDC(), _rcSaveSlot[2]);	
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_rcSaveSlot[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("activetextbox")->render(getMemDC(), _rcSaveSlot[i].left, _rcSaveSlot[i].top, 0, 0,
					_rcSaveSlot[i].right - _rcSaveSlot[i].left, _rcSaveSlot[i].bottom - _rcSaveSlot[i].top);
			}//���콺 �������� Ȱ��ȭ

			if (_setSaveSlot == i)
			{
				IMAGEMANAGER->findImage("activetextbox")->render(getMemDC(), _rcSaveSlot[i].left, _rcSaveSlot[i].top, 0, 0,
					_rcSaveSlot[i].right - _rcSaveSlot[i].left, _rcSaveSlot[i].bottom - _rcSaveSlot[i].top);
			}
		}


		FrameRect(getMemDC(), _rcSaveSlot[0], RGB(255, 255, 255));				 //���̺꽽�� �������ֱ�
		FrameRect(getMemDC(), _rcSaveSlot[1], RGB(255, 255, 255));				 //���̺꽽�� �������ֱ�
		FrameRect(getMemDC(), _rcSaveSlot[2], RGB(255, 255, 255));				 //���̺꽽�� �������ֱ�

		Rectangle(getMemDC(), _rcSave);
		frameBoxRender(_rcSave, 0.3f);															//���̺� ��ư �̹���..�̾�..
		IMAGEMANAGER->findImage("save")->render(getMemDC(), _rcSave.left-1, _rcSave.top-1);

		Rectangle(getMemDC(), _rcLoad);
		frameBoxRender(_rcLoad, 0.3f);															//�ε� ��ư ���������� �̹��� ������..
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

	_rcSaveLoad = RectMake(_rcPalette.left + 480, _rcPalette.top, 96, 48);							//���� UI
	_rcDummy1 = RectMake(_rcPalette.left + 480, _rcPalette.top + 48, 96, 48);						//���� UI
	_rcDummy2 = RectMake(_rcPalette.left + 480, _rcPalette.top + 96, 96, 48);						//���� UI
	_rcDummy3 = RectMake(_rcPalette.left + 480, _rcPalette.top + 144, 96, 48);						//���� UI
	_rcslide = RectMake(_rcPalette.left + 480, _rcPalette.top + 192, 96, 48);						//���� UI
	_rcArrow[0] = RectMake(_rcPalette.left + 480, _rcPalette.top + 240, 48, 48);					//���� UI
	_rcArrow[1] = RectMake(_rcPalette.left + 528, _rcPalette.top + 240, 48, 48);					//���� UI

	_rcSaveWindow = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2-50, 300, 250);					    //���̺�ε�UI
	for (int i = 0; i < 3; i++)																	    //���̺�ε�UI
	{																							    //���̺�ε�UI
		_rcSaveSlot[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 125 + i * 49, 250,50);		    //���̺�ε�UI
	}																							    //���̺�ε�UI
	_rcSave = RectMakeCenter(WINSIZEX/2-70,WINSIZEY/2+35,80,35);								    //���̺�ε�UI
	_rcLoad = RectMakeCenter(WINSIZEX/2+70,WINSIZEY/2+35,80,35);								    //���̺�ε�UI

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
				//�����ư�� ������Ʈ��?
				if (_layer[1])
				{
					_tiles[i].canMove[1] = _canMove;
					_tiles[i].tileFrameX[1] = _currentTile.x;
					_tiles[i].tileFrameY[1] = _currentTile.y;
					_tiles[i].imagePage[1] = _currentTile.pageNumber;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//�����ư�� ���찳��?
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


	//�����ӹٵ�
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), left, top, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), left + width -(17*scale), top, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), left, top+height - (17*scale), scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), left + width - (17 * scale), top + height - (17 * scale), scale);
	//�𼭸�

}
void maptoolScene::frameBoxRender(RECT rc, float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left-17 * scale, rc.top-1, 0, 0, 17 * scale, rc.bottom+1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right, rc.top-1, 0, 0, 17 * scale, rc.bottom+1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left-1, rc.top-17 * scale, 0, 0, rc.right+1 - rc.left, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left-1,rc.bottom, 0, 0, rc.right+1 - rc.left, 17 * scale, scale);


	//�����ӹٵ�
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left-17 * scale, rc.top-17 * scale, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right, rc.top-17 * scale, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left-17 * scale, rc.bottom , scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right, rc.bottom, scale);

	//�𼭸�

}



//void maptoolScene::frameBoxRender(RECT rc, float scale)
//{
//	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
//	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, 0, 0, 17 * scale, rc.bottom - rc.top, scale);
//	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left, rc.top, 0, 0, rc.right - rc.left, 17 * scale, scale);
//	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left, rc.top + rc.bottom - rc.top - (17 * scale), 0, 0, rc.right - rc.left, 17 * scale, scale);
//
//
//	//�����ӹٵ�
//	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left, rc.top, scale);
//	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.top, scale);
//	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left, rc.bottom - (17 * scale), scale);
//	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right - (17 * scale), rc.bottom - (17 * scale), scale);
//	//�𼭸�
//
//}  //��Ʈ ���ο� �׸��°� Ȥ�þ������־ �ּ�ó��

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
