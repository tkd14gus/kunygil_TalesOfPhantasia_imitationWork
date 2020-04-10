#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{

	//플레이어 클래스 초기화
	_player = new player;
	_player->init();
	
	//제일 처음 시작할 때 시작 위치는 village(마을)
	_mapLocation = 0;

	//카메라는 항상 중앙을 비치고 있어야 한다.
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	//맵을 불러와 셋팅해준다.
	this->mapSetting(_mapLocation);
	//타일을 플레이어 위치에 맞게 조정해준다.
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

	//인게임에서 방향키를 누른다면 타일들도 같이 움직여준다.
	if (INPUT->GetKey(VK_UP))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.top++;
			_tiles[i].rc.bottom++;
			//만약 플레이어의 Y좌표가 WINSIZEY / 2보다 위에 있으면 더이상 올라가면 안된다.
			//그걸 계산해줘서 타일의 움직임을 제안한다.
			//아래의 모든 타일의 움직임을 제안하는 if문은 같은 원리이다.
			if (_player->getPlayerY() <= WINSIZEY / 2)
			{
				_tiles[i].rc.top--;
				_tiles[i].rc.bottom--;
			}
			//만약 플레이어의 Y좌표가 (48 * 150 - WINSIZEY / 2)아래에 있으면 타일이 움직이면 안되기 때문에 1씩 빼준다.
			if (_player->getPlayerY() >= (48 * 150 - WINSIZEY / 2))
			{
				_tiles[i].rc.top--;
				_tiles[i].rc.bottom--;
			}
		}
	}
	//인게임에서 방향키를 누른다면 타일들도 같이 움직여준다.
	if (INPUT->GetKey(VK_DOWN))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.top--;
			_tiles[i].rc.bottom--;
			//만약 플레이어의 Y좌표가 WINSIZEY / 2보다 위에 있으면 타일이 움직이면 안되기 때문에 1씩 더해준다.
			if (_player->getPlayerY() <= WINSIZEY / 2)
			{
				_tiles[i].rc.top++;
				_tiles[i].rc.bottom++;
			}
			//만약 플레이어의 Y좌표가 (48 * 150 - WINSIZEY / 2)이상이면 더이상 올라가면 안된다.
			if (_player->getPlayerY() >= (48 * 150 - WINSIZEY / 2))
			{
				_tiles[i].rc.top++;
				_tiles[i].rc.bottom++;
			}
		}
	}
	//인게임에서 방향키를 누른다면 타일들도 같이 움직여준다.
	if (INPUT->GetKey(VK_RIGHT))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.left--;
			_tiles[i].rc.right--;
			//만약 플레이어의 X좌표가 (48 * 120 - WINSIZEX / 2) - 40이상이면 더이상 이동하면 안된다.
			if (_player->getPlayerX() >= (48 * 120 - WINSIZEX / 2))
			{
				_tiles[i].rc.left++;
				_tiles[i].rc.right++;
			}
			//만약 플레이어의 X좌표가  WINSIZEX / 2 - 40보다 위에 있으면 타일이 움직이면 안되기 때문에 1씩 더해준다.
			if (_player->getPlayerX() <= WINSIZEX / 2)
			{
				_tiles[i].rc.left++;
				_tiles[i].rc.right++;
			}
		}
	}
	//인게임에서 방향키를 누른다면 타일들도 같이 움직여준다.
	if (INPUT->GetKey(VK_LEFT))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc.left++;
			_tiles[i].rc.right++;
			//만약 플레이어의 X좌표가  WINSIZEX / 2 - 40보다 위에 있으면 타일이 움직이면 안되기 때문에 1씩 더해준다.
			if (_player->getPlayerX() <= WINSIZEX / 2)
			{
				_tiles[i].rc.left--;
				_tiles[i].rc.right--;
			}
			//만약 플레이어의 X좌표가 (48 * 120 - WINSIZEX / 2) - 40이상이면 더이상 이동하면 안된다.
			if (_player->getPlayerX() >= (48 * 120 - WINSIZEX / 2))
			{
				_tiles[i].rc.left--;
				_tiles[i].rc.right--;
			}
		}
	}

	_player->update();

	//만약 마을일 때
	if (_mapLocation == 0)
	{
		//플레이어의 x가 일정수치 이상으로 오른쪽으로 이동한다면 필드로 이동
		if (_player->getPlayerX() >= (48 * 120 - 32))
		{
			_mapLocation = 1;
			this->mapSetting(_mapLocation);
			//player렉트의 넓이가 64이니 절반인 32보다 조금 더 주고,
			//Player렉트의 높이가 128이니 절반인 64보다 조금 더 준다.
			_player->setPlayerRect(50, 80);
			//타일을 플레이어 위치에 맞게 조정해준다.
			this->tileSetting();
		}
	}
	//만약 필드일 때
	else if (_mapLocation == 1)
	{
		//플레이어의 x가 일정수치 이상으로 왼쪽으로 이동한다면 마을로 이동
		if (_player->getPlayerX() <= 32)
		{
			_mapLocation = 0;
			this->mapSetting(_mapLocation);
			//player렉트의 넓이가 64이니 절반인 32보다 조금 더해서 맵의 오른쪽에 나오도록,
			//Player렉트의 높이가 128이니 절반인 64보다 조금 더 준다.
			_player->setPlayerRect(48 * 120 - 50, 80);
			//타일을 플레이어 위치에 맞게 조정해준다.
			this->tileSetting();
		}
	}

	//문과 충돌하는지 확인을 위한 for문
	//안에 내용은 나중에 채워놓을 것
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&rc, &_player->getPlayerDoorRc(), &_tiles[i].rc))
		{
			//레이아웃이 3개이므로 3번 더 돌려준다.
			for (int j = 0; j < 3; j++)
			{
				//만일 페이지, 프레임X, 프레임Y가 모두 "문"이미지와 같다면
				//열리는 이미지로 바꿔주는 코드를 채워놓을 것
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
	//플레이어가 있는 곳을 중심으로 타일을 옮겨준다.
	for (int i = 0; i < TILEX * TILEY; i++)
	{

		//현재 플레이어의 위치만큼 조정을 하려면 _tiles[i].rc를 움직여야 한다.
		//이 때 _tiles[i].rc의 기본 위치가 플레이어가 WINSIZEX / 2, WINSIZEY / 2일때 이므로 현 위치에서 중심일 때 좌표를 빼주면
		//이동한 값이 나온다.
		//추가 - 현재 타일들의 가장 상단으론 30, 좌측으로 40만큼 타일이 더 들어가 있음. 그것을들 추가로 계산해줘서 타일의 위치 조정
		//그만큼을 빼주면 원하는 값이 나온다.
		//모두 동일

		//만약 y좌표가 WINSIZEY / 2보다 작을 때
		if (_player->getPlayerY() <= WINSIZEY / 2)
		{
			//top, bottom은 변동사항 없음
		}
		//만약 y좌표가 (48 * 150 - WINSIZEY / 2)보다 크다면
		else if (_player->getPlayerY() >= (48 * 150 - WINSIZEY / 2))
		{
			//(48 * 150 - WINSIZEY / 2)는 화면밖으로 안 나가도록 타일이 이 고정된 곳이다.
			//이 위치는 전체 HEIGHT에서 WINSIZEY만큼 뺀 값과 같다.
			//때문에 타일의 top과 bottom에서 전체 높이에서 WINSIZEY를 뺀 값만큼 빼주면
			//가장 하단의 타일이 카메라 렉트 안으로 들어온다.
			//x좌표 동일
			_tiles[i].rc.top -= (48 * 150 - WINSIZEY);
			_tiles[i].rc.bottom -= (48 * 150 - WINSIZEY);
		}
		//만약 y좌표가  WINSIZEY / 2보다 크고, (48 * 150 - WINSIZEY / 2)보다 작다면
		else
		{
			//_tiles[i].rc의 기본 위치가 플레이어가 WINSIZEX / 2, WINSIZEY / 2일때 이므로 현 위치에서 중심일 때 좌표를 빼주면
			//이동한 값이 나온다.
			//추가 - 현재 타일들의 가장 상단으론 30, 좌측으로 40만큼 타일이 더 들어가 있음. 그것을들 추가로 계산해줘서 타일의 위치 조정
			//그만큼을 빼주면 원하는 값이 나온다.
			//x좌표 동일
			_tiles[i].rc.top -= (_player->getPlayerRc().top - (WINSIZEY / 2 - 64));
			_tiles[i].rc.bottom -= (_player->getPlayerRc().bottom - (WINSIZEY / 2 + 64));
		}

		//만약 x좌표가 WINSIZEX / 2 보다 작을 때
		if (_player->getPlayerX() <= WINSIZEX / 2)
		{
			//left, right는 병동사항 없음
		}
		//만약 x좌표가 (48 * 120 - WINSIZEX / 2)보다 크다면
		else if (_player->getPlayerX() >= (48 * 120 - WINSIZEX / 2))
		{
			_tiles[i].rc.left -= (48 * 120 - WINSIZEX);
			_tiles[i].rc.right -= (48 * 120 - WINSIZEX);
		}
		//만약 x좌표가  WINSIZEX / 2보다 크고, (48 * 120 - WINSIZEX / 2)보다 작다면
		else
		{
			_tiles[i].rc.left -= (_player->getPlayerRc().left - (WINSIZEX / 2 - 32));
			_tiles[i].rc.right -= (_player->getPlayerRc().right - (WINSIZEX / 2 + 32));
		}
	}
}
