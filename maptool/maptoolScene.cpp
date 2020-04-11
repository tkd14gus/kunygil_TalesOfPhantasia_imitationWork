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
	//����Ÿ��(0,0)��ǥ�� �ʱ�ȭ
	_currentTile.pageNumber = _palettePage;
	_currentTile.x = 0;
	_currentTile.y = 0;

	//���� �巡�� ��ǥ �ʱ�ȭ(���� ������� ����)
	_currentTile.sampleStartX = 0;
	_currentTile.sampleStartY = 0;
	_currentTile.sampleEndX = 0;
	_currentTile.sampleEndY = 0;
	_currentTile.sampleSizeX = 1;
	_currentTile.sampleSizeY = 1;
	_currentTile.sampleStartPointX = 0;
	_currentTile.samplSetartPointY = 0;

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
					if (INPUT->GetKeyUp(VK_LEFT)) { _sampleTile[i].direct[2] = !_sampleTile[i].direct[2]; }
					if (INPUT->GetKeyUp(VK_RIGHT)) { _sampleTile[i].direct[3] = !_sampleTile[i].direct[3]; }
					break;
				}
			}
		}
	}
	else if (_setSaveLoad == true) // ���̺� Ȯ��â�� ��������
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{

			if (PtInRect(&_rcSaveSlot[0], _ptMouse))
			{
				_setSaveSlot = 0;
			}	//����1������
			if (PtInRect(&_rcSaveSlot[1], _ptMouse))
			{
				_setSaveSlot = 1;
			}	//����2������
			if (PtInRect(&_rcSaveSlot[2], _ptMouse))
			{
				_setSaveSlot = 2;
			}	//����3������

			if (_setSaveSlot == 0)
			{
				sprintf_s(_mapName, "save1.mapsave");
			}	//����1���������� �̸�����
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
		_rcMouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 48, 48);

		//#====================================================================================================
		//#				�ءء� �ʵ� �ءء� ��� ���
		//#				�����͸� ����ϱ� ���� ĥ�� Ÿ���� �����͸� ����ϴ��� ������ ���� X
		//#				���Ŀ� ���� �ǵ��� �۾��� �����̸�
		//#				�� ���� ������ �� �����ϸ� �ΰ��ӿ��� �������ϴ�
		//#=====================================================================================================
		if (INPUT->GetKeyDown(VK_D))
		{
			//����Ÿ�� ������ ����Ʈ 
			loadMapData(_dataName);
			_editMode = true;
		}

		this->maptoolSetup();

		if (_rcPalette.top > WINSIZEY) // �ּ�ȭ�� ȭ������� �����鼭 ���ϸ�ŭ�������� ��ư����(�̵�) �ظ��� �¾����� �ؿ��־����
		{
			_rcSaveLoad = RectMake(_rcPalette.left, WINSIZEY - 48, 96, 48);							//���� UI
			_rcEraser = RectMake(_rcPalette.left + 96, WINSIZEY - 48, 96, 48);						//���� UI
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

		//���̾� ����
		if (INPUT->GetKeyDown(VK_1)) { selectLayer1(); }
		if (INPUT->GetKeyDown(VK_2)) { selectLayer2(); }
		if (INPUT->GetKeyDown(VK_3)) { selectLayer3(); }

		//ȭ�� �̵�
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

		//�����Ͱ� ����Ÿ�� ���� �ִٸ� ����Ÿ�� ����
		//�����Ͱ� ��Ÿ�� ���� �ִٸ� ���õǾ� �ִ� ����Ÿ���� ��Ÿ�Ͽ� ĥ���ش�.

		//��ư Ŭ�� �κ�
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rcEraser, _ptMouse))
			{
				//�̰� ���Ѱ���
				_currentTile.pageNumber = -1;
			}
			if (PtInRect(&_rcDummy2, _ptMouse))
			{
				SCENEMANAGER->loadScene("����ȭ��");	//���� ȭ������ ���ư���
			}
			if (PtInRect(&_rcDummy3, _ptMouse))
			{
			}

			if (PtInRect(&_rcslide, _ptMouse))
			{
				if (_slideTool == false) { _slideTool = true; }
				else if (_slideTool == true) { _slideTool = false; }
			}
			if (PtInRect(&_rcArrow5[0], _ptMouse) && _palettePage - 4 > 1)			//����Ÿ���� ��ȣ�� 1���� Ŭ ��
			{
				_palettePage -= 5;													//����Ÿ���� ��ȣ�� 1 ���ҽ�Ű��
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//�ش� ����Ÿ���� �ȷ�Ʈ�� �׷��ش�.
			}
			if (PtInRect(&_rcArrow5[1], _ptMouse) && _palettePage + 4 < SMAPLETILECOUNT)			//����Ÿ���� ��ȣ�� �ִ밪���� ���� ��
			{
				_palettePage += 5;													//����Ÿ���� ��ȣ�� 1 ������Ű��
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//�ش� ����Ÿ���� �ȷ�Ʈ�� �׷��ش�.
			}
			if (PtInRect(&_rcArrow[0], _ptMouse) && _palettePage > 1)			//����Ÿ���� ��ȣ�� 1���� Ŭ ��
			{
				_palettePage--;													//����Ÿ���� ��ȣ�� 1 ���ҽ�Ű��
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//�ش� ����Ÿ���� �ȷ�Ʈ�� �׷��ش�.
			}
			if (PtInRect(&_rcArrow[1], _ptMouse) && _palettePage < SMAPLETILECOUNT)			//����Ÿ���� ��ȣ�� �ִ밪���� ���� ��
			{
				_palettePage++;													//����Ÿ���� ��ȣ�� 1 ������Ű��
				sprintf_s(_imageName, "map%d", _palettePage);
				sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//�ش� ����Ÿ���� �ȷ�Ʈ�� �׷��ش�.
			}


			//����Ÿ�� ������ Ŭ������ ���
			for (int i = 0; i < SMAPLETILECOUNT; i++) {
				if (PtInRect(&_sampleTile[i].rc, _ptMouse)) {
					_currentTile.sampleStartX = _ptMouse.x;		//���� x��ǥ
					_currentTile.sampleStartY = _ptMouse.y;		//���� y��ǥ

					//������ ���� ���콺 ��ǥ�� ���������淡 �ӽ÷� ������
					_currentTile.sampleStartPointX = 0;		//���� x������ ��ǥ
					_currentTile.samplSetartPointY = 0;		//���� y������ ��ǥ
				}
			}
		}


		if (INPUT->GetKeyUp(VK_LBUTTON)) {
			if (PtInRect(&_rcSaveLoad, _ptMouse))
			{
				_setSaveLoad = true;
			}

			//����Ÿ�� ������ ���콺�� ���� ��� �巡���� ��������ǥ�� �����´�(Ÿ�� �巡�� ����)
			for (int i = 0; i < SMAPLETILECOUNT; i++) {
				if (PtInRect(&_sampleTile[i].rc, _ptMouse)) {
					_currentTile.sampleEndX = _ptMouse.x;
					_currentTile.sampleEndY = _ptMouse.y;

					if (_currentTile.sampleEndX <= _currentTile.sampleStartX) {
						_currentTile.sampleEndX = _currentTile.sampleStartX;
					}

					if (_currentTile.sampleEndY <= _currentTile.sampleStartY) {
						_currentTile.sampleEndY = _currentTile.sampleStartY;
					}

					//������ ���� �귯�� �����
					this->setSample();
				}
			}
		}

		if (INPUT->GetKey(VK_LBUTTON)) this->setMap();//Ÿ�� �� ĭ ä���

		if (INPUT->GetKey('A') && INPUT->GetKey(VK_LBUTTON)) this->setAllMap();//Ÿ�� ���� ä���+�����
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

	//���̾� �̹��� �׸���
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

		//�ϴ��� ����Ÿ�� ���� �����Ϸ����� 16->48�ȼ��� Ȯ��

		_sampleTile[i].tileFrameX = i % 10;
		_sampleTile[i].tileFrameY = i / 10;
		_sampleTile[i].imagePage = _palettePage;

		sprintf(_pageNum, "page : %d", _palettePage);
		sprintf(_pageName, "map%d", _palettePage);
		IMAGEMANAGER->findImage(_pageName)->scaleFrameRender(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, i % 10, i / 10, 3.0f);

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


	//Rectangle(getMemDC(), _rcSaveLoad);			//�̹��� ����� Rectangle ��� �̹����� ����ؾ� ��.
	//Rectangle(getMemDC(), _rcDummy2);			//�̹��� ����� Rectangle ��� �̹����� ����ؾ� ��.
	//Rectangle(getMemDC(), _rcDummy3);			//�̹��� ����� Rectangle ��� �̹����� ����ؾ� ��.
	//Rectangle(getMemDC(), _rcslide);			//�̹��� ����� Rectangle ��� �̹����� ����ؾ� ��.
	IMAGEMANAGER->findImage("Eraser")->render(getMemDC(), _rcEraser.left, _rcEraser.top);			//���찳 �̹��� ���
	if (PtInRect(&_rcEraser, _ptMouse)) {
		IMAGEMANAGER->findImage("EraserOff")->render(getMemDC(), _rcEraser.left, _rcEraser.top);
	}

	IMAGEMANAGER->findImage("homeoff")->render(getMemDC(), _rcDummy2.left, _rcDummy2.top);
	if (PtInRect(&_rcDummy2, _ptMouse)) {
		IMAGEMANAGER->findImage("home")->render(getMemDC(), _rcDummy2.left, _rcDummy2.top);
	}

	IMAGEMANAGER->findImage("saveLoadOff")->render(getMemDC(), _rcSaveLoad.left, _rcSaveLoad.top);
	if (PtInRect(&_rcSaveLoad, _ptMouse)) {
		IMAGEMANAGER->findImage("saveLoad")->render(getMemDC(), _rcSaveLoad.left, _rcSaveLoad.top);
	}

	IMAGEMANAGER->findImage("slideOff")->render(getMemDC(), _rcslide.left, _rcslide.top);
	if (PtInRect(&_rcslide, _ptMouse)) {
		IMAGEMANAGER->findImage("slide")->render(getMemDC(), _rcslide.left, _rcslide.top);
	}

	frameBoxRender(_rcPalette, 1.0f);

	HBRUSH brush = CreateSolidBrush(RGB(16, 64, 168));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), _rcArrow5[0].left, _rcArrow5[0].top, _rcArrow5[1].right, _rcArrow5[1].bottom);
	Rectangle(getMemDC(), _rcArrow[0].left, _rcArrow[0].top, _rcArrow[1].right, _rcArrow[1].bottom);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);


	//����Ÿ���� ��ȣ�� 1���� ���� ���� �����Ƿ� 1���� ū ��쿡�� ���� Ÿ�Ϸ� �Ѿ�� ȭ��ǥ�� �����ش�.
	if (_palettePage > 1) { IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	if (_palettePage > 1) { IMAGEMANAGER->findImage("leftArrow5")->render(getMemDC(), _rcArrow5[0].left, _rcArrow5[0].top); }
	//����Ÿ���� ��ȣ�� �ִ밪���� ū ���� �����Ƿ� �ִ밪���� ���� ��쿡�� ���� Ÿ�Ϸ� �Ѿ�� ȭ��ǥ�� �����ش�.
	if (_palettePage < SMAPLETILECOUNT) { IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }
	if (_palettePage < SMAPLETILECOUNT) { IMAGEMANAGER->findImage("rightArrow5")->render(getMemDC(), _rcArrow5[1].left, _rcArrow5[1].top); }


	if (_setSaveLoad == true)
	{
		frameBoxRender(_rcSaveWindow, 1.0f); //���̺�Ȯ��â������

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
		IMAGEMANAGER->findImage("save")->render(getMemDC(), _rcSave.left - 1, _rcSave.top - 1);

		Rectangle(getMemDC(), _rcLoad);
		frameBoxRender(_rcLoad, 0.3f);															//�ε� ��ư ���������� �̹��� ������..
		IMAGEMANAGER->findImage("load")->render(getMemDC(), _rcLoad.left - 1, _rcLoad.top - 1);

	}

	//char temp[100];
	textOut(getMemDC(), 100, 100, _pageNum, RGB(255, 0, 0));

	//�巡�� ���� ���̰� �ϱ�(�ӽ�)
	if (PtInRect(&_rcPalette, _ptMouse) && INPUT->GetKey(VK_LBUTTON)) {
		Rectangle(getMemDC(), _currentTile.sampleStartX, _currentTile.sampleStartY, _ptMouse.x, _ptMouse.y);
	}

	//�巡�� ��ǥ ����� ��µǴ��� ���� ���Դϴ� ���߿� ����ϴ�
	wsprintf(count, TEXT("���õ� xŸ�� ����:%d,���õ� yŸ�� ����:%d"), _currentTile.sampleSizeX, _currentTile.sampleSizeY);
	TextOut(getMemDC(), 100, 250, count, strlen(count));
	wsprintf(drag, TEXT("������x,y:%d,%d, ����x,y:%d,%d, ���� ��ǥ:%d,%d, ����ǥ:%d,%d"),
		_currentTile.sampleStartX, _currentTile.sampleStartY, _currentTile.sampleEndX, _currentTile.sampleEndY,
		_currentTile.sampleStartPointX, _currentTile.samplSetartPointY, _currentTile.sampleEndPointX, _currentTile.sampleEndPointY);
	TextOut(getMemDC(), 100, 200, drag, strlen(drag));

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

	_rcSaveLoad = RectMake(_rcPalette.left + 480, _rcPalette.top, 96, 48);							//���� UI 1��ĭ
	_rcEraser = RectMake(_rcPalette.left + 480, _rcPalette.top + 48, 96, 48);						//���� UI 2��ĭ
	_rcDummy2 = RectMake(_rcPalette.left + 480, _rcPalette.top + 96, 96, 48);						//���� UI 3��ĭ
	_rcslide = RectMake(_rcPalette.left + 480, _rcPalette.top + 144, 96, 48);						//���� UI 4��ĭ
	//_rcDummy3 = RectMake(_rcPalette.left + 480, _rcPalette.top + 192, 96, 48);					//���� UI 5��ĭ
	_rcArrow5[0] = RectMake(_rcPalette.left + 480, _rcPalette.top + 192, 48, 48);
	_rcArrow5[1] = RectMake(_rcPalette.left + 528, _rcPalette.top + 192, 48, 48);
	_rcArrow[0] = RectMake(_rcPalette.left + 480, _rcPalette.top + 240, 48, 48);					//���� UI �ǾƷ���ĭ
	_rcArrow[1] = RectMake(_rcPalette.left + 528, _rcPalette.top + 240, 48, 48);					//���� UI �ǾƷ���ĭ

	_rcSaveWindow = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 50, 300, 250);					    //���̺�ε�UI
	for (int i = 0; i < 3; i++)																	    //���̺�ε�UI
	{																							    //���̺�ε�UI
		_rcSaveSlot[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 125 + i * 49, 250, 50);		    //���̺�ε�UI
	}																							    //���̺�ε�UI
	_rcSave = RectMakeCenter(WINSIZEX / 2 - 70, WINSIZEY / 2 + 35, 80, 35);								    //���̺�ε�UI
	_rcLoad = RectMakeCenter(WINSIZEX / 2 + 70, WINSIZEY / 2 + 35, 80, 35);								    //���̺�ε�UI

}

void maptoolScene::setSample() {
	//���õ� x����Ÿ�� ����
	_currentTile.sampleSizeX = (_currentTile.sampleEndX - _currentTile.sampleStartX) / 48 + 1;
	//���õ� y����Ÿ�� ����
	_currentTile.sampleSizeY = (_currentTile.sampleEndY - _currentTile.sampleStartY) / 48 + 1;

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

}

void maptoolScene::setMap()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			//���� �ϴ� ���̾��ΰ�
			if (_layer[0])
			{
				_tiles[i].canMove[0] = _canMove;
				_tiles[i].imagePage[0] = _currentTile.pageNumber;
				_tiles[i].tileFrameX[0] = _currentTile.x;
				_tiles[i].tileFrameY[0] = _currentTile.y;
				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			//�߰� ���̾��ΰ�
			if (_layer[1])
			{
				_tiles[i].canMove[1] = _canMove;
				_tiles[i].tileFrameX[1] = _currentTile.x;
				_tiles[i].tileFrameY[1] = _currentTile.y;
				_tiles[i].imagePage[1] = _currentTile.pageNumber;
				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			//���� �� ���̾��ΰ�
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

void maptoolScene::setAllMap() {
	for (int i = 0; i < TILEX * TILEY; i++) {
		//���� �ϴ� ���̾�
		if (_layer[0])
		{
			_tiles[i].canMove[0] = _canMove;
			_tiles[i].imagePage[0] = _currentTile.pageNumber;
			_tiles[i].tileFrameX[0] = _currentTile.x;
			_tiles[i].tileFrameY[0] = _currentTile.y;

			//���⼭ ä��
			_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
		}
		//�߰� ���̾�
		if (_layer[1])
		{
			_tiles[i].canMove[1] = _canMove;
			_tiles[i].tileFrameX[1] = _currentTile.x;
			_tiles[i].tileFrameY[1] = _currentTile.y;
			_tiles[i].imagePage[1] = _currentTile.pageNumber;
			_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
		}
		//���� �� ���̾�
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

void maptoolScene::uiMove()
{

}

void maptoolScene::save(char* str)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

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
		WriteFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX - 2) * SAMPLETILEY, &write, NULL);
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

void maptoolScene::frameBoxRender(int left, int top, int width, int height, float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), left, top, 0, 0, 17 * scale, height, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), left + width - (17 * scale), top, 0, 0, 17 * scale, height, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), left, top, 0, 0, width, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), left, top + height - (17 * scale), 0, 0, width, 17 * scale, scale);


	//�����ӹٵ�
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), left, top, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), left + width - (17 * scale), top, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), left, top + height - (17 * scale), scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), left + width - (17 * scale), top + height - (17 * scale), scale);
	//�𼭸�

}
void maptoolScene::frameBoxRender(RECT rc, float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left - 17 * scale, rc.top - 1, 0, 0, 17 * scale, rc.bottom + 1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right, rc.top - 1, 0, 0, 17 * scale, rc.bottom + 1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left - 1, rc.top - 17 * scale, 0, 0, rc.right + 1 - rc.left, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left - 1, rc.bottom, 0, 0, rc.right + 1 - rc.left, 17 * scale, scale);


	//�����ӹٵ�
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left - 17 * scale, rc.top - 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right, rc.top - 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left - 17 * scale, rc.bottom, scale);
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
