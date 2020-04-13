#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{

	//처음엔 상태창을 키지 않은 상태이다.
	_isStateWinOpen = false;

	//플레이어 클래스 초기화
	_player = new player;
	_player->init();
	_subPlayer = new subplayer;
	_subPlayer->init();
	//제일 처음 시작할 때 시작 위치는 village(마을)
	_mapLocation = 0;

	//카메라는 항상 중앙을 비치고 있어야 한다.
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	//맵을 불러와 셋팅해준다.
	this->mapSetting(_mapLocation);
	//타일을 플레이어 위치에 맞게 조정해준다.
	this->tileSetting();

	//만일 PLAYERDATA->getPlayerData()가 NULL이 아닐 때
	//(제일 먼저 켜지면 NULL로 초기화됨)
	//_player에 넣어준다.
	if (PLAYERDATA->getPlayerData() != NULL)
	{
		_player = PLAYERDATA->getPlayerData();
	}
	//만일 PLAYERDATA->getTilesRC()[0].left가 0이라면
	//배틀신으로 이동한 적이 없다는 말이다.
	//즉, 렉트의 이동이 없었으므로 굳이 데이터를 저장할 필요 없다.
	if (PLAYERDATA->getTilesRC()[0].left != 0)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].rc = PLAYERDATA->getTilesRC()[i];
		}
	}

	//state렉트 위치에 맞게 초기화
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
	//상태창이 열리지 않은 상태라면.
	if (!_isStateWinOpen)
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
			//필드일때
			if (_mapLocation == 1)
			{
				//걸음마다 배틀씬으로 바꿀건지 확인해준다.
				this->changeBattleScene();
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
			//필드일때
			if (_mapLocation == 1)
			{
				//걸음마다 배틀씬으로 바꿀건지 확인해준다.
				this->changeBattleScene();
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
			//필드일때
			if (_mapLocation == 1)
			{
				//걸음마다 배틀씬으로 바꿀건지 확인해준다.
				this->changeBattleScene();
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
			//필드일때
			if (_mapLocation == 1)
			{
				//걸음마다 배틀씬으로 바꿀건지 확인해준다.
				this->changeBattleScene();
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

		//S키를 누르면 상태창이 뜬다.
		//한번만 확인해줄거니까 GetKeyDown으로 해준다.
		if (INPUT->GetKeyDown('S'))
		{
			//상태창을 연다.
			_isStateWinOpen = true;
			//상태창에서 계쏙 걸어야 하니까 상태를 걷기로 바꿔준다.
			_player->setPlayerState(pWALK);
			//나올 때 원래 바라보고 있던 방향으로 볼거니까 원래 바라보던 방향을 저장한다.
			_saveDirect = _player->getDirect();
			//상태창에서 처음 걸을 때 방향은 아래 즉 1이다.
			_player->setDirect(1);
		}
	}
	//상태창이 열렸다면
	else
	{
		//S키를 다시 누르면 나가진다.
		//한번만 확인해줄거니까 GetKeyDown으로 해준다.
		if (INPUT->GetKeyDown('S'))
		{
			//상태창을 연다.
			_isStateWinOpen = false;
			//나오자마자 상태는 IDLE이다.
			_player->setPlayerState(pIDLE);
			//플레이어가 바라볼 방향을 다시 돌려준다.
			_player->setDirect(_saveDirect);
		}
	}

}

void inGameScene::render()
{
	//상태창이 열려있지 않다면
	if (!_isStateWinOpen)
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
	//상태창이 열려있다면
	else
	{
		//일단 상태창 배경화면을 보여주고
		IMAGEMANAGER->render("stateWindow", getMemDC());

		//위치 확인용 렉트
		//for (int i = 0; i < 4; i++)
		//{
		//	Rectangle(getMemDC(), _stateRC[i]);
		//}
		//플레이어의 이미지가 걷는거 업데이트
		_player->spinPlayer();
		//위의 업데이트를 기반으로 이미지 출력
		IMAGEMANAGER->scaleFrameRender("cress", getMemDC(), _stateRC[0].right - 50, _stateRC[0].top + 20, IMAGEMANAGER->findImage("cress")->getFrameX(), IMAGEMANAGER->findImage("cress")->getFrameY(), 0.5f);

		//서브 캐릭터의 이미지가 걷는 모습 업데이트
		_subPlayer->walkingInfo();
		//위의 업데이트를 기반으로 이미지 출력
		IMAGEMANAGER->findImage("chester")->scaleFrameRender(getMemDC(), _stateRC[1].right - 50, _stateRC[1].top + 20,
			IMAGEMANAGER->findImage("chester")->getFrameX(), IMAGEMANAGER->findImage("chester")->getFrameY(), 1.0f);

		//TEXT의 색을 바꿔준다.
		//하얀색
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		//레벨 출력
		sprintf(_stateWin, "LV : %d", _player->getPlayer()->lv);
		TextOut(getMemDC(), _stateRC[0].left + 20, _stateRC[0].top + 50, _stateWin, strlen(_stateWin));
		sprintf(_stateWin, "LV : %d", _subPlayer->getSubPlayer()->lv);
		TextOut(getMemDC(), _stateRC[1].left + 20, _stateRC[1].top + 50, _stateWin, strlen(_stateWin));
		//최대 HP와 현재 HP출력
		//Y축만 위에것보다 30 더해줬음
		sprintf(_stateWin, "HP : %d / %d", _player->getPlayer()->hp, _player->getPlayer()->maxHp);
		TextOut(getMemDC(), _stateRC[0].left + 20, _stateRC[0].top + 80, _stateWin, strlen(_stateWin));
		sprintf(_stateWin, "HP : %d / %d", _subPlayer->getSubPlayer()->hp, _subPlayer->getSubPlayer()->maxHp);
		TextOut(getMemDC(), _stateRC[1].left + 20, _stateRC[1].top + 80, _stateWin, strlen(_stateWin));
		//최대 TP와 현재 TP출력
		//Y축만 위에것보다 30 더해줬음
		sprintf(_stateWin, "TP : %d / %d", _player->getPlayer()->tp, _player->getPlayer()->maxTp);
		TextOut(getMemDC(), _stateRC[0].left + 20, _stateRC[0].top + 110, _stateWin, strlen(_stateWin));
		sprintf(_stateWin, "TP: %d / %d", _subPlayer->getSubPlayer()->tp, _subPlayer->getSubPlayer()->maxTp);
		TextOut(getMemDC(), _stateRC[1].left + 20, _stateRC[1].top + 110, _stateWin, strlen(_stateWin));
		//다시 검정색으로 바꿔주자
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

void inGameScene::changeBattleScene()
{
	//아직 전투씬이 완성 안 되어 있어서 일단 주석처리
	//int ran = RANDOM->Range(500);
	//
	//if(ran % 500 == 0)
	//{
	//	SCENEMANAGER->loadScene("전투화면");
	//	//플레이어 정보도 저장해준다.
	//	PLAYERDATA->setPlayerData(_player);
	//	//타일의 렉트 위치 저장
	//	PLAYERDATA->setTilesRC(_tiles)
	//}
}
