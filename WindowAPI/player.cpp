#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	// 플레이어 구조체를 init시키면 초기화 시켜준다.
	this->settingTagPlayer();

	//_stage = RectMake(0, 500, WINSIZEX, 300);

	//프레임이미지초기화
	_frameCount = 0;
	_frameIndex = 0;
	_player.viewX = 0;
	//무적시간 초기화
	//_immoTime = 0;

	//_enemyHP = 3;


	//_enemyX = 500;
	//_enemyY = 400;

	// 게임이 시작할 때 전투씬이 아니다.
	_isBattle = true;
	// 플레이어는 제일 먼저 시작할 때 아래를 바라보고 있다.
	_direct = 1;
	_player.cameraRc = RectMakeCenter(_player.x, _player.y, 300, 200);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (_isBattle)
	{
		//실시간 플레이어 위치 및 속도
		_player.rc = RectMakeCenter(_player.x, _player.y, 75, 80);
		_player.cameraRc = RectMakeCenter(_player.x, _player.y, 300, 200);
	
		if (!(_player._state == pATTACK || _player._state == pJUMP))
		{
			_player.attXK = 0;
			_player.attYK = 0;
		}
		if (_player.sight == true)	//플레이어가 오른쪽을 바라보고 있을 때
		{
			_player.attack = RectMake(_player.rc.right - 20, _player.rc.top, _player.attXK, _player.attYK);
			//_player.jumpAttack = RectMake(_rcPlayer.right - 20, _rcPlayer.top, 50, 160);
		}
		else if (_player.sight == false)  //플레이어가 왼쪽을 바라보고 있을 때
		{
			_player.attack = RectMake(_player.rc.left - 20, _player.rc.top, _player.attXK, _player.attYK);
			//_player.jumpAttack = RectMake(_rcPlayer.left - 20, _rcPlayer.top, 50, 160);
		}
		//공격용 렉트
		if (_player._state == pWALK)
		{
			_player.speed = 3.0f;
		}
		else if (_player._state == pRUN)
		{
			_player.speed = 5.0f;
		}

		//실시간 적의 위치
		//_TESTenemy = RectMake(_enemyX, _enemyY, 50, 50);

		//적사각형 중점
		//_enemyCenterX = _enemyX + float((_TESTenemy.right - _TESTenemy.left) / 2);
		//_enemyCenterY = _enemyY + float((_TESTenemy.bottom - _TESTenemy.top) / 2);

		//test - HP down
		if (INPUT->GetKeyDown('Q'))
		{
			_player.hp--;
			if (_player.hp <= 0)
			{
				_frameIndex = 0;
			}
		}
		if (INPUT->GetKeyDown('W'))
		{
			_player.hp++;
			_player._state = pIDLE;
		}
		if (INPUT->GetKeyDown('E'))
		{
			_player.gravity = 3.f;
			_player._state = pHIT;
			_frameIndex = 0;
			_frameCount = 0;
		}
		//액션테스트

		//sight left & walk left
		if (INPUT->GetKey(VK_LEFT))
		{
			if (_player._state == pATTACK)
			{
				_player._state = pATTACK;
			}
			else if (_player._state == pGUARD)
			{
				_player.sight = 0;
				_player._state = pGUARD;
			}
			else if (_player._state == pJUMP)
			{
				_player._state = pJUMP;
				if (_player.viewX == 0 && _player.x > 37) { _player.x -= 3; }
				else if (_player.cameraRc.left < 0) { _player.viewX -= 3; }
				else { _player.x -= 3; }
			}
			else if (_player._state == pHIT)
			{
				_player._state = pHIT;
			}
			else if (_player._state == pWIN)
			{
				_player._state = pWIN;
			}
			else if (_player._state == pDEAD)
			{
				_player._state = pDEAD;
				if (_frameIndex >= 2)
				{
					_player.sight = 0;					 //플레이어 시점 - 왼쪽
					if (_player.viewX == 0 && _player.x > 37) { _player.x -= _player.speed; }
					else if (_player.cameraRc.left < 0) { _player.viewX -= _player.speed; }
					else { _player.x -= _player.speed; }	  //플레이어 좌표 변화
				}
			}
			else
			{
				if (INPUT->GetKey(VK_SHIFT))
				{
					_player.sight = 0;				 //플레이어 시점 - 왼쪽
					_player._state = pRUN;			 //플레이어 상태 - 뛰기
					if (_player.viewX == 0 && _player.x > 37) { _player.x -= _player.speed; }
					else if (_player.cameraRc.left < 0) { _player.viewX -= _player.speed; }
					else { _player.x -= _player.speed; }    //플레이어 좌표 변화
				}
				else
				{
					_player.sight = 0;				 //플레이어 시점 - 왼쪽
					_player._state = pWALK;			 //플레이어 상태 - 걷기
					if (_player.viewX ==0  && _player.x > 37) { _player.x -= _player.speed; }
					else if (_player.cameraRc.left < 0) { _player.viewX -= _player.speed; }
					else { _player.x -= _player.speed; }      //플레이어 좌표 변화
				}
			}
		}
		//state idle
		if (INPUT->GetKeyUp(VK_LEFT) && _player._state != pATTACK 
			&& _player._state != pWIN && _player._state != pDEAD)
		{
			if (_player._state != pGUARD)
			{
				if (_player._state != pHIT)
				{
					_player._state = pIDLE;
				}
			}
		}
		//sight right & walk right
		if (INPUT->GetKey(VK_RIGHT))
		{
			if (_player._state == pATTACK)
			{
				_player._state = pATTACK;
			}
			else if (_player._state == pGUARD)
			{
				_player.sight = 1;
				_player._state = pGUARD;
			}
			else if (_player._state == pJUMP)
			{
				_player._state = pJUMP;
				if (_player.viewX == 900 && _player.x < WINSIZEX-37) { _player.x += _player.speed; }
				else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += 3; }
				else { _player.x += 3; }
			}
			else if (_player._state == pHIT)
			{
				_player._state = pHIT;
			}
			else if (_player._state == pWIN)
			{
				_player._state = pWIN;
			}
			else if (_player._state == pDEAD)
			{
				_player._state = pDEAD;
				if (_frameIndex >= 2)
				{
					_player.sight = 1;				 //플레이어 시점 - 왼쪽
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x += _player.speed; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += _player.speed; }
					else { _player.x += _player.speed; }                //플레이어 좌표 변화
				}
			}
			else
			{
				if (INPUT->GetKey(VK_SHIFT))
				{
					
					_player.sight = 1;				 //플레이어 시점 - 오른쪽
					_player._state = pRUN;			         //플레이어 상태 - 뛰기
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x += _player.speed; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += _player.speed; }
					else { _player.x += _player.speed; }                 //플레이어 좌표 변화
				}
				else
				{
					_player.sight = 1;				 //플레이어 시점 - 오른쪽
					_player._state = pWALK;			         //플레이어 상태 - 걷기
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x += _player.speed; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX += _player.speed; }
					else { _player.x += _player.speed; }                  //플레이어 좌표 변화
				}
			}
		}
		//state idle
		if (INPUT->GetKeyUp(VK_RIGHT) && _player._state != pATTACK  
			&& _player._state != pWIN && _player._state != pDEAD)
		{

			if (_player._state != pGUARD)
			{
				if (_player._state != pHIT)
				{
					_player._state = pIDLE;
				}
			}
		}


		//test - state attack -> 베기와 찌르기, 점프시에는 점프 베기 찌르기등으로 추가예정
		if (INPUT->GetKeyDown('Z') && _player._state != pDEAD && _player._state != pJUMP && _player._state != pHIT && _player._state != pWIN && _player._state != pDEAD && _player._state != pATTACK)
		{
			_player._state = pATTACK;
			if (_player._state != pATTACK)
			{
				_frameIndex = 0;
			}

			_player.attXK = 50;
			_player.attYK = 130;

		}

		//test - state guard
		if (INPUT->GetKey('X') && _player._state != pJUMP && _player._state != pHIT 
			&& _player._state != pWIN && _player._state != pDEAD)
		{
			_player._state = pGUARD;
		}
		if (INPUT->GetKeyUp('X') && _player._state != pHIT && _player._state != pWIN && _player._state != pDEAD)
		{
			_player._state = pIDLE;
		}

		// state jump
		if (INPUT->GetKeyDown('C') && _player._state != pJUMP && _player._state != pWIN && _player._state != pDEAD)
		{
			if (_player._state != pHIT)
			{
				_frameIndex = 0;
				_player._state = pJUMP;
				_player.gravity = 0.0f;
				_player.attXK = 50;
				_player.attYK = 130;
			}
		}

		if (_player._state == pJUMP || _player._state == pHIT)
		{
			_player.x += cosf(PI / 2) * 1;
			_player.y += -sinf(PI / 2) * 5 + _player.gravity;
			_player.gravity += 0.1f;
		}



		//test - state win
		if (INPUT->GetKeyDown(VK_F5))
		{
			_frameIndex = 0;
			_frameCount = 0;
			_player._state = pWIN;
		}

		//바닥에 닿게 되었을때
		if (_player.y > 460 && _player._state == pJUMP)
		{
			_player.gravity = 0.0f;
			_player._state = pIDLE;
			_player.y = 460;
		}
		if (_player.y > 470 && _player._state == pHIT)
		{

			_player.y = 470;
		}
		//공중에서 다른 모션이 적용되지 않도록 설정
		if (_player.y < 460 && _player._state != pJUMP)
		{
			if (_player._state != pHIT)
			{
				_player._state = pJUMP;
			}
		}
		if (_player.y < 460 && _player._state != pHIT)
		{
			if (_player._state != pJUMP)
			{
				_player._state = pHIT;
			}
		}
		//플레이어 사망
		if (_player.hp <= 0)
		{
			if (_player._state != pDEAD)
			{
				_frameCount = 0;
				IMAGEMANAGER->findImage("dead")->setFrameX(0);
			}
			_player._state = pDEAD;
			_player.rc = RectMakeCenter(_player.x - 75 / 2, _player.y - 80 / 2, 0, 0);

			if (_frameCount > 200)
			{
				SCENEMANAGER->loadScene("시작화면");
			}
		}
		if (_player._state == pWIN)
		{
			_player._state = pWIN;
		}

		if (_player.viewX < 0) { _player.viewX = 0; }
		else if (_player.viewX > 900) { _player.viewX = 900; }

		//RECT temp;
		////공격 타격범위와 적과의 충돌
		//if (IntersectRect(&temp, &_player.attack, &_TESTenemy))
		//{
		//	_player.attXK = 0;
		//	_player.attYK = 0;
		//	_enemyHP -= 1;
		//}
	}
	else
	{
	// 위쪽키를 눌렀을 때
	if (INPUT->GetKey(VK_UP))
	{
		//움직이면 먼저 상태를 walk로 바꿔준다.
		_player._state = pWALK;
		//움직이는 뱡항을 조정해준다.
		//위쪽이므로 0.
		_direct = 0;
		//위쪽으로 움직이므로 Y좌표만 --시켜준다.
		_player.inGameY--;
	}
	// 위쪽키를 땠을 떄
	if (INPUT->GetKeyUp(VK_UP))
	{
		//움직임을 idle로 바꿔준다.
		_player._state = pIDLE;
	}
	// 아래쪽키를 눌렀을 때
	if (INPUT->GetKey(VK_DOWN))
	{
		//움직이면 먼저 상태를 walk로 바꿔준다.
		_player._state = pWALK;
		//움직이는 뱡항을 조정해준다.
		//위쪽이므로 1
		_direct = 1;
		//위쪽으로 움직이므로 Y좌표만 ++시켜준다.
		_player.inGameY++;
	}
	// 아래쪽키를 땠을 떄
	if (INPUT->GetKeyUp(VK_DOWN))
	{
		//움직임을 idle로 바꿔준다.
		_player._state = pIDLE;
	}
	// 왼쪽키를 눌렀을 때
	if (INPUT->GetKey(VK_LEFT))
	{
		//움직이면 먼저 상태를 walk로 바꿔준다.
		_player._state = pWALK;
		//움직이는 뱡항을 조정해준다.
		//위쪽이므로 2.
		_direct = 2;
		//위쪽으로 움직이므로 X좌표만 --시켜준다.
		_player.inGameX--;
	}
	// 왼쪽키를 땠을 떄
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		//움직임을 idle로 바꿔준다.
		_player._state = pIDLE;
	}
	// 오른쪽키를 눌렀을 때
	if (INPUT->GetKey(VK_RIGHT))
	{
		//움직이면 먼저 상태를 walk로 바꿔준다.
		_player._state = pWALK;
		//움직이는 뱡항을 조정해준다.
		//위쪽이므로 3.
		_direct = 3;
		//위쪽으로 움직이므로 X좌표만 ++시켜준다.
		_player.inGameX++;
	}
	// 오른쪽키를 땠을 떄
	if (INPUT->GetKeyUp(VK_RIGHT))
	{
		//움직임을 idle로 바꿔준다.
		_player._state = pIDLE;
	}

	// 플레이어의 위치를 계속 초기화 한다.
	_player.rc = RectMakeCenter(_player.inGameX, _player.inGameY, 64, 128);
	// 플레이어의 문 충돌용 렉트 위치를 계속 초기화 한다.
	this->settingPlayerDoorRect();
	//_playerDoorRcP = RectMakeCenter(_player.inGameX, _player.inGameY, 64 + 48 * 2, 128 + 48 * 2);

	}

	_frameCount++;

}

void player::render()
{
	//배틀일 때
	if (_isBattle)
	{
				
		//Rectangle(getMemDC(), _stage);

		Rectangle(getMemDC(), _player.rc);		//플레이어 타격범위 사각형

		Rectangle(getMemDC(), _player.attack);		//플레이어 타격범위 사각형

		FrameRect(getMemDC(), _player.cameraRc, RGB(140, 60, 180));

		this->animation();					//플레이어 모션 애니메이션
											//배틀일 땐 애니메이션으로 렌더하니까 뒤에 둔다.

		SetTextColor(getMemDC(), RGB(255, 255, 255));

		char chr1[100];
		sprintf_s(chr1, "player hp : %d", _frameCount);
		TextOut(getMemDC(), 100, 720, chr1, strlen(chr1));

		sprintf_s(chr1, "player hp : %d", _player.hp);
		TextOut(getMemDC(), 100, 680, chr1, strlen(chr1));
		SetTextColor(getMemDC(), RGB(0, 0, 0));

	}
	else
	{
		this->animation();					//플레이어 모션 애니메이션
											//배틀이 아닐땐 프레임X, Y값을 바꿔주기 때문에 가장 먼저 함수를 불러준다.

		//문 충돌을 위한 렉트 보여주기
		FrameRect(getMemDC(), _playerDoorRc, RGB(255, 0, 0));

		// 플레이어가 걷는 상태라면
		if (_player._state == pWALK)
		{
			//만약 플레이어의 x값이 WINSIZEX / 2보다 크고, (48 * 120 - WINSIZEX / 2)보다 작을때(x값이 가운데일 때)
			if (_player.inGameX >= WINSIZEX / 2 && _player.inGameX <= (48 * 120 - WINSIZEX / 2))
			{
				//만약 y값도 가운데라면
				if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
				{
					//렉트할 때 중심에 그리는 것이 아니라 left, top의 좌표이므로 절반 크기만큼 빼준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, WINSIZEY / 2 - 64);
				}
				//y값이 위쪽에 치우쳐져 있다면
				else if (_player.inGameY < WINSIZEY / 2)
				{
					//x는 중심값, y는 캐릭터의 top값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top);
				}
				//y값이 아래쪽에 치우쳐져 있다면
				else
				{
					//x는 중심값, y는 (48 * 150 - WINSIZEY)값에서 플레이어 top값을 뺀 값을 준다.
					//_player.rc.top - (48 * 150 - WINSIZEY)인 이유는 플레이어의 위치를 WINSIZEY안에 그려줘야 하는데
					//y좌표는 이미  WINSIZEY를 초과한 상태이다.
					//때문에 현재 좌표에서 전체 맵 크기인 48 * 150와 화면 Y축 크기인 WINSIZEY을 뺀 값을
					//플레이어 좌표에서 빼주면 화면에 보이면서  WINSIZEY 안에서 플레이어를 랜더한 수 있다.
					//이후로 나오는 Y좌표와 X좌표 모두 같은 원리이다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top - (48 * 150 - WINSIZEY));
				}

			}
			//만약 플레이어의 y값이 WINSIZEY / 2보다 크고, (48 * 150 - WINSIZEY / 2)보다 작을 때(y값이 가운데일 때)
			else if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
			{
				//만약 x값이 왼쪽이라면
				if (_player.inGameX < WINSIZEX / 2)
				{
					//플레이어의 x값은 플레이어의 값을, y값은 중심값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, WINSIZEY / 2 - 64);
				}
				//만약 x값이 오른쪽이라면
				else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
				{
					//플레이어의 x값은 _player.rc.left - (48 * 120 - WINSIZEX)값을 , y값은 중심값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), WINSIZEY / 2 - 64);
				}
			}
			//플래이어 x가 왼쪽에 치우쳐져 있을 때
			else if (_player.inGameX < WINSIZEX / 2)
			{
				//만약 y가 위쪽에 치우쳐져 있다면
				if (_player.inGameY < WINSIZEY / 2)
				{
					//x플레이어의 원래 x값, y는 캐릭터의 top값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top);
				}
				//y값이 아래쪽에 치우쳐져 있다면
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//x플레이어의 원래 x값, y는 캐릭터의  _player.rc.top - (48 * 150 - WINSIZEY)값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top - (48 * 150 - WINSIZEY));
				}
			}
			//플레이어 x가 오른쪽에 치우쳐져 있을 때
			else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
			{
				//만약 y가 위쪽에 치우쳐져 있다면
				if (_player.inGameY < WINSIZEY / 2)
				{
					//플레이어x는  _player.rc.left - (48 * 120 - WINSIZEX)값, y는 캐릭터의 top값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top);
				}
				//y값이 아래쪽에 치우쳐져 있다면
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//플레이어의x는 _player.rc.left - (48 * 120 - WINSIZEX)값, y는 캐릭터의  _player.rc.top - (48 * 150 - WINSIZEY)값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top - (48 * 150 - WINSIZEY));
				}
			}
		}
		// 플레이어가 멈춰있는 상태라면 currentX좌표는 항상 2번으로 멈춰있다.
		// 때문에 walk일때와 다르게 뒤에 2,  _directP); 를 추가로 더해준다.
		else
		{
			//만약 플레이어의 x값이 WINSIZEX / 2보다 크고, (48 * 120 - WINSIZEX)보다 작을때(x값이 가운데일 때)
			if (_player.inGameX >= WINSIZEX / 2 && _player.inGameX <= (48 * 120 - WINSIZEX / 2))
			{
				//만약 y값도 가운데라면
				if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
				{
					//렉트할 때 중심에 그리는 것이 아니라 left, top의 좌표이므로 절반 크기만큼 빼준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, WINSIZEY / 2 - 64, 2, _direct);
				}
				//y값이 위쪽에 치우쳐져 있다면
				else if (_player.inGameY < WINSIZEY / 2)
				{
					//x는 중심값, y는 캐릭터의 top값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top, 2, _direct);
				}
				//y값이 아래쪽에 치우쳐져 있다면
				else
				{
					//플레이어의x는 중심에서 넓이의 절반만큼 뺀 WINSIZEX / 2 - 32를 주고,, y는 캐릭터의  _player.rc.top - (48 * 150 - WINSIZEY)값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), WINSIZEX / 2 - 32, _player.rc.top - (48 * 150 - WINSIZEY), 2, _direct);
				}

			}
			//만약 플레이어의 y값이 WINSIZEY / 2보다 크고, (48 * 150 - WINSIZEY / 2)보다 작을 때(y값이 가운데일 때)
			else if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
			{
				//만약 x값이 왼쪽이라면
				if (_player.inGameX < WINSIZEX / 2)
				{
					//플레이어의 x값은 플레이어의 값을, y값은 중심값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, WINSIZEY / 2 - 64, 2, _direct);
				}
				//만약 x값이 오른쪽이라면
				else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
				{
					//플레이어의 x값은 _player.rc.left - (48 * 120 - WINSIZEX / 2)값을 , y값은 중심값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), WINSIZEY / 2 - 64, 2, _direct);
				}
			}
			//플래이어 x가 왼쪽에 치우쳐져 있을 때
			else if (_player.inGameX < WINSIZEX / 2)
			{
				//만약 y가 위쪽에 치우쳐져 있다면
				if (_player.inGameY < WINSIZEY / 2)
				{
					//x플레이어의 원래 x값, y는 캐릭터의 top값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top, 2, _direct);
				}
				//y값이 아래쪽에 치우쳐져 있다면
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//x플레이어의 원래 x값, y는 캐릭터의  _player.rc.top - (48 * 150 - WINSIZEY / 2)값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left, _player.rc.top - (48 * 150 - WINSIZEY), 2, _direct);
				}
			}
			//플레이어 x가 오른쪽에 치우쳐져 있을 때
			else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
			{
				//만약 y가 위쪽에 치우쳐져 있다면
				if (_player.inGameY < WINSIZEY / 2)
				{
					//플레이어x는  _player.rc.left - (48 * 120 - WINSIZEX / 2)값, y는 캐릭터의 top값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top, 2, _direct);
				}
				//y값이 아래쪽에 치우쳐져 있다면
				else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
				{
					//플레이어의x는 _player.rc.left - (48 * 120 - WINSIZEX / 2)값, y는 캐릭터의  _player.rc.top - (48 * 150 - WINSIZEY / 2)값을 준다.
					IMAGEMANAGER->frameRender("cress", getMemDC(), _player.rc.left - (48 * 120 - WINSIZEX), _player.rc.top - (48 * 150 - WINSIZEY), 2, _direct);
				}
			}
		}

	}
}

void player::animation()
{
	//배틀일 때
	if (_isBattle)
	{
		switch (_player._state)
		{
		case pIDLE:		//대기상태
			//좌
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("mIdle", getMemDC(), _player.rc.left, _player.rc.top + 3);
				//_frameCount++;
				_player.idle->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 0;
					}
					_player.idle->setFrameX(_frameIndex);
				}
			}
			//우
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("mIdle", getMemDC(), _player.rc.left, _player.rc.top + 3);
				//_frameCount++;
				_player.idle->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.idle->setFrameX(_frameIndex);
				}
			}
			break;
		case pWALK:		//걷기
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("walk", getMemDC(), _player.rc.left - 10, _player.rc.top + 2);
				//_frameCount++;
				_player.walk->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.walk->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("walk", getMemDC(), _player.rc.left + 10, _player.rc.top + 2);
				//_frameCount++;
				_player.walk->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.walk->setFrameX(_frameIndex);
				}
			}
			break;
		case pRUN:		//달리기
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("run", getMemDC(), _player.rc.left - 10, _player.rc.top - 5);
				//_frameCount++;
				_player.run->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.run->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("run", getMemDC(), _player.rc.left, _player.rc.top - 5);
				//_frameCount++;
				_player.run->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.run->setFrameX(_frameIndex);
				}
			}
			break;
		case pATTACK:	//공격은 한번공격후 다시 대기상태로 들어가게 했음
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("slash", getMemDC(), _player.rc.left - 15, _player.rc.top - 10);
				//_frameCount++;
				_player.atkSlash->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("slash")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameCount = 0;
						_frameIndex = 0;
						_player._state = pIDLE;	//한번공격후 상태대기자세로
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("slash", getMemDC(), _player.rc.left - 10, _player.rc.top - 10);
				//_frameCount++;
				_player.atkSlash->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("slash")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
						_player._state = pIDLE;
					}
					_player.atkSlash->setFrameX(_frameIndex);
				}
			}
			break;
		case pJUMP:
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("jump", getMemDC(), _player.rc.left, _player.rc.top - 20);
				//_frameCount++;
				_player.jump->setFrameY(1);
				if (_frameCount % 15 == 0)
				{
					IMAGEMANAGER->findImage("jump")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameCount = 0;
						_frameIndex = 3;
					}
					_player.jump->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("jump", getMemDC(), _player.rc.left, _player.rc.top - 20);
				//_frameCount++;
				_player.jump->setFrameY(0);
				if (_frameCount % 15 == 0)
				{
					IMAGEMANAGER->findImage("jump")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameCount = 0;
						_frameIndex = 3;
					}
					_player.jump->setFrameX(_frameIndex);
				}
			}
			break;
		case pGUARD:		//가드
			if (_player.sight == false)
			{
				IMAGEMANAGER->frameRender("guard", getMemDC(), _player.rc.left, _player.rc.top);
				//_frameCount++;
				_player.guard->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("guard")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 1)
					{
						_frameCount = 0;
						_frameIndex = 0;
					}
					_player.guard->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				IMAGEMANAGER->frameRender("guard", getMemDC(), _player.rc.left, _player.rc.top);
				//_frameCount++;
				_player.guard->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("guard")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 1)
					{
					}
					_player.guard->setFrameX(_frameIndex);
				}
			}
			break;
		case pDEAD:		//사망시에는 hp = 0이되어 사망하며 유령상태 유지 - 이후 재시작등 수정 가능
			if (_player.sight == false)
			{
				if (_frameIndex >= 2) { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top + 18); }
				//_frameCount++;
				_player.dead->setFrameY(0);
				if (_frameCount % 30 == 0)
				{
					IMAGEMANAGER->findImage("dead")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameIndex = 2;
					}
					_player.dead->setFrameX(_frameIndex);
				}
			}
			else if (_player.sight == true)
			{
				if (_frameIndex >= 2) { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("dead", getMemDC(), _player.rc.left + 20, _player.rc.top + 18); }
				//_frameCount++;
				_player.dead->setFrameY(1);
				if (_frameCount % 30 == 0)
				{
					IMAGEMANAGER->findImage("dead")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameIndex = 2;
					}
					_player.dead->setFrameX(_frameIndex);
				}
			}
			break;
		case pWIN:
			IMAGEMANAGER->frameRender("win", getMemDC(), _player.rc.left - 20, _player.rc.top - 54);
			//_frameCount++;
			_player.win->setFrameY(0);
			if (_frameCount % 20 == 0)
			{
				IMAGEMANAGER->findImage("win")->setFrameY(0);
				_frameIndex++;
				_player.win->setFrameX(_frameIndex);
				if (_frameIndex == 7)
				{
					_isBattle = false;
					_player.viewX = 0;
					_player.x = 200;
					_player.y = 460;
					//SCENEMANAGER->loadScene("게임화면");
				}
			}
			break;
		case pHIT:		//히트시 날아가서 눕고 프레임 올라가는속도 / 인덱스0,1위치차이 등 예외적용한게 많음
			
			if (_player.sight)
			{
				if (_frameIndex == 0) { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 3); }
				_player.hit->setFrameY(0);
				if (_frameCount % 80 < 50 && _frameIndex == 0) 
				{
					if (_player.viewX == 0 && _player.x > 37) { _player.x --; }
					else if (_player.cameraRc.left < 0) { _player.viewX --; }
					else { _player.x --; }
				}
				if (_frameCount == 80 || _frameCount >= 120)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 0;
						_player._state = pIDLE;
						_player.y = 460;
					}
					_player.hit->setFrameX(_frameIndex);
				}
			}
			else
			{
				if (_frameIndex == 0) { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 10); }
				else { IMAGEMANAGER->frameRender("hit", getMemDC(), _player.rc.left, _player.rc.top + 3); }
				_player.hit->setFrameY(1);
				if (_frameCount % 80 < 50 && _frameIndex == 0)
				{
					if (_player.viewX == 900 && _player.x < WINSIZEX - 37) { _player.x ++; }
					else if (_player.cameraRc.right > WINSIZEX) { _player.viewX ++; }
					else { _player.x ++; }
				}
				if (_frameCount == 80 || _frameCount >= 120)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 0;
						_player._state = pIDLE;
						_player.y = 460;
					}
					_player.hit->setFrameX(_frameIndex);
				}
			}
			break;
		}
	}
	//배틀이 아닐 때
	else
	{
		// 플레이어가 걷는 상태라면
		if (_player._state == pWALK)
		{
			// _directP가 바라보는 방향인데 바라보는 방향에 따라
			// 프레임이미지의 Y좌표가 달라짐.
			switch (_direct)
			{
				//위쪽키를 눌렀을 떄
			case 0:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(0);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
				//아래쪽키를 눌렀을 떄
			case 1:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(1);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
				//왼쪽키를 눌렀을 떄
			case 2:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(2);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
				//오른쪽키를 눌렀을 때
			case 3:
				if (_frameCount % 8 == 0)
				{
					IMAGEMANAGER->findImage("cress")->setFrameY(3);
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("cress")->setFrameX(_frameIndex);
				}
				break;
			}
		}
	}
}


void player::setAction(int pattern)
{
	tagstate state;
	if (pattern == 1) { state = pIDLE; }
	else if (pattern == 2) { state = pRUN; }
	else if (pattern == 3) { state = pHIT; }
	else if (pattern == 4) { state = pWALK; }
	else if (pattern == 5) { state = pJUMP; }
	else if (pattern == 6) { state = pATTACK; }
	else if (pattern == 7) { state = pGUARD; }
	else if (pattern == 8) { state = pDEAD; }
	else if (pattern == 8) { state = pWIN; }
	if (_player._state != state)
	{
		_frameIndex = 0;
	}
	_player._state = state;
}

void player::playerWin()
{
	if (_player._state != pWIN && !(_player._state == pJUMP || _player._state == pATTACK))
	{
		_frameIndex = 0;
		_frameCount = 0;
		_player._state = pWIN;
	}
}
void player::playerHit()
{
	_player.hp--;
	if (_player.hp > 0)
	{
		_player.gravity = 3.f;
		_player._state = pHIT;
	}
	_frameIndex = 0;
	_frameCount = 0;
}


void player::setPlayerRect(int x, int y)
{
	_player.inGameX = x;
	_player.inGameY = y;
	_player.rc = RectMakeCenter(_player.inGameX, _player.inGameY, 64, 128);
}


void player::settingTagPlayer()
{

	//이미지 초기화
	_player.idle = IMAGEMANAGER->addFrameImage("mIdle", "Images/mainplayer/idle.bmp", 150, 156, 2, 2);
	_player.walk = IMAGEMANAGER->addFrameImage("walk", "Images/mainplayer/walk.bmp", 360, 156, 4, 2);
	_player.run = IMAGEMANAGER->addFrameImage("run", "Images/mainplayer/run&stop.bmp", 450, 188, 5, 2);
	_player.guard = IMAGEMANAGER->addFrameImage("guard", "Images/mainplayer/guard.bmp", 66, 156, 1, 2);

	//공격모션
	_player.atkSlash = IMAGEMANAGER->addFrameImage("slash", "Images/mainplayer/atk_slash.bmp", 525, 262, 5, 2);
	//_player.atkstab = IMAGEMANAGER->addFrameImage("stab", "Images/mainplayer/atk_stab.bmp", 396, 120, 4, 2);
	_player.jump = IMAGEMANAGER->addFrameImage("jump", "Images/mainplayer/jump_slash.bmp", 445, 262, 5, 2);

	_player.dead = IMAGEMANAGER->addFrameImage("dead", "Images/mainplayer/dead.bmp", 250, 120, 4, 2);

	_player.win = IMAGEMANAGER->addFrameImage("win", "Images/mainplayer/victory.bmp", 401, 157, 4, 1);

	//히트모션 추가 - 구민본
	_player.hit = IMAGEMANAGER->addFrameImage("hit", "Images/mainplayer/hit.bmp", 137, 140, 2, 2);

	//플레이어 초기 좌표 설정
	_player.x = 200;
	_player.y = 460;
	//플레이어 사각형


	_player.sight = true;		//초기 설정 - 오른쪽 방향
	//_player.atkTime = 0.0f;     //타격시간
	_player._state = pIDLE;		        //초기 설정 - 대기상태


	_player.speed = 3.0f;


	_player.hp = _player.maxHp = 5;			//초기 설정 - 체력 5
	_player.tp = _player.maxTp = 5;			//초기 설정 - TP 5
	_player.lv = 1;
	_player.attXK = 0;
	_player.attYK = 0;

	//인게임에서 사용할 좌표는 배틀과 겹치면 안되니까 따로 빼놓자.
	_player.inGameX = (48 * 120) - WINSIZEX;
	_player.inGameY = (48 * 150) - WINSIZEY;
	//플레이어 렉트를 초기화 해준다.
	_player.rc = RectMakeCenter(_player.inGameX, _player.inGameY, 64, 128);
}

void player::settingPlayerDoorRect()
{
	//계산신의 위의 render에 frameRender와 같음.
	//궁금하면 거기 봐볼것.
	//다만 rect크기가 두개 타일 크기인 48 * 2만큼 더 크므로
	//그것을 감안하여 계산함.

	//만약 플레이어의 x값이 WINSIZEX / 2보다 크고, (48 * 120 - WINSIZEX / 2)보다 작을때(x값이 가운데일 때)
	if (_player.inGameX >= WINSIZEX / 2 && _player.inGameX <= (48 * 120 - WINSIZEX / 2))
	{
		//만약 y값도 가운데라면
		if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
		{
			_playerDoorRc = RectMake(WINSIZEX / 2 - 80, WINSIZEY / 2 - 112, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y값이 위쪽에 치우쳐져 있다면
		else if (_player.inGameY < WINSIZEY / 2)
		{
			_playerDoorRc = RectMake(WINSIZEX / 2 - 80, _player.rc.top - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y값이 아래쪽에 치우쳐져 있다면
		else
		{
			_playerDoorRc = RectMake(WINSIZEX / 2 - 80, _player.rc.top - (48 * 150 - WINSIZEY) - 48, 64 + 48 * 2, 128 + 48 * 2);
		}

	}
	//만약 플레이어의 y값이 WINSIZEY / 2보다 크고, (48 * 150 - WINSIZEY / 2)보다 작을 때(y값이 가운데일 때)
	else if (_player.inGameY >= WINSIZEY / 2 && _player.inGameY <= (48 * 150 - WINSIZEY / 2))
	{
		//만약 x값이 왼쪽이라면
		if (_player.inGameX < WINSIZEX / 2)
		{
			_playerDoorRc = RectMake(_player.rc.left - 48, WINSIZEY / 2 - 112, 64 + 48 * 2, 128 + 48 * 2);
		}
		//만약 x값이 오른쪽이라면
		else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
		{
			_playerDoorRc = RectMake(_player.rc.left - (48 * 120 - WINSIZEX) - 48, WINSIZEY / 2 - 112, 64 + 48 * 2, 128 + 48 * 2);
		}
	}
	//플래이어 x가 왼쪽에 치우쳐져 있을 때
	else if (_player.inGameX < WINSIZEX / 2)
	{
		//만약 y가 위쪽에 치우쳐져 있다면
		if (_player.inGameY < WINSIZEY / 2)
		{
			_playerDoorRc = RectMake(_player.rc.left - 48, _player.rc.top - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y값이 아래쪽에 치우쳐져 있다면
		else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
		{
			_playerDoorRc = RectMake(_player.rc.left - 48, _player.rc.top - (48 * 150 - WINSIZEY) - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
	}
	//플레이어 x가 오른쪽에 치우쳐져 있을 때
	else if (_player.inGameX > (48 * 120 - WINSIZEX / 2))
	{
		//만약 y가 위쪽에 치우쳐져 있다면
		if (_player.inGameY < WINSIZEY / 2)
		{
			_playerDoorRc = RectMake(_player.rc.left - (48 * 120 - WINSIZEX) - 48, _player.rc.top - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
		//y값이 아래쪽에 치우쳐져 있다면
		else if (_player.inGameY > (48 * 150 - WINSIZEY / 2))
		{
			_playerDoorRc = RectMake(_player.rc.left - (48 * 120 - WINSIZEX) - 48, _player.rc.top - (48 * 150 - WINSIZEY) - 48, 64 + 48 * 2, 128 + 48 * 2);
		}
	}
}

void player::spinPlayer()
{
	//stateWindow가 참이되면 플레이어를 update 안하기 때문에 여기서 프레임카운터를 증가시킨다.
	_frameCount++;

	//40프레임이 지날때 마다 보는 방향을 바꿔준다.
	//순서는 아래 좌 위 우이다.
	if (_frameCount % 500 == 0)
	{
		if (_direct == 0)
			_direct = 3;
		else if (_direct == 1)
			_direct++;
		else if (_direct == 2)
			_direct = 0;
		else
			_direct = 1;
	}
	//
	this->animation();
}

HRESULT subplayer::init()
{

								//이미지 초기화
	//대기 모션
	_subPlayer.idle = IMAGEMANAGER->addFrameImage("subIdle", "Images/subplayer/chester_battel_idle.bmp", 154, 182, 2, 2);
	//걷기 모션
	_subPlayer.walk = IMAGEMANAGER->addFrameImage("subWalk", "Images/subplayer/chester_battel_walk.bmp", 328, 184, 4, 2);
	//달리기 모션
	_subPlayer.run = IMAGEMANAGER->addFrameImage("subRun", "Images/subplayer/chester_battel_run.bmp", 344, 172, 4, 2);
	//원거리 공격 모션
	_subPlayer.atkshot = IMAGEMANAGER->addFrameImage("subShot", "Images/subplayer/chester_battel_shoot.bmp", 728, 198, 8, 2);
	//근접 공격 모션
	_subPlayer.atkmelee = IMAGEMANAGER->addFrameImage("subMelee", "Images/subplayer/chester_battel_physical.bmp", 202,180,2, 2);
	//사망 모션
	_subPlayer.dead = IMAGEMANAGER->addFrameImage("subDead", "Images/subplayer/chester_battel_dead.bmp", 279, 210, 3, 2);
	//승리 모션
	_subPlayer.win = IMAGEMANAGER->addFrameImage("subWin", "Images/subplayer/chester_battel_win.bmp", 285, 236, 3, 2);
	//화살 이미지
	_arrow._img = IMAGEMANAGER->addFrameImage("arrow", "Images/subplayer/arrow.bmp", 76, 22, 1, 2);
								//이미지 초기화 끝
	_walkingDirect = IMAGEMANAGER->addFrameImage("chester", "Images/subplayer/chester_walking_direct.bmp", 165, 256, 5, 4);




	//플레이어 초기 좌표 설정
	_subPlayer.x = 200;
	_subPlayer.y = 414;
	//플레이어 사각형



	_subPlayer.sight = true;	//초기 설정 - 오른쪽 방향
	_subPlayer._state = pIDLE;		        //초기 설정 - 대기상태

	_arrow._chargeTime = 0.0f;	//화살준비 시간. (일정 시간에 도달하면 발사)
	_arrow._bShoot = false;		//화살이 발사되었는지 판단하는 bool 변수.
								//true일 경우 발사된 것으로 판단하므로 false로 초기화.
	_arrow._speed = 0.0f;		//화살이 날아가는 속도 초기화.
	_partyDistance = 0.0f;
	_enemyDistance = 0.0f;

	_melee = false;				//거리가 일정 거리가 될경우 true값이 되어 공격시 근접공격으로 전환

	_subPlayer.hp = _subPlayer.maxHp = 5;			//초기 설정 - 체력 5
	_subPlayer.tp = _subPlayer.maxTp = 5;
	_subPlayer.lv = 1;
	_subPlayer.attXK = 0;
	_subPlayer.attYK = 0;


	//프레임이미지초기화
	_frameCount = 0;
	_frameIndex = 0;

	return S_OK;
}

void subplayer::release()
{

}

void subplayer::update(int playerViewX)
{
	this->animation();


	//ai의 위치
	_subPlayer.viewX = _subPlayer.x - playerViewX;
	_subPlayer.rc = RectMake(_subPlayer.viewX, _subPlayer.y, 77, 91);
	
	//이동 상태에 따른 속도 변경
	if (_subPlayer._state == pWALK) 
	{
		_subPlayer.speed = 1.0f;	//pWALK일 때는 속도를 1.0f로 설정
		if (_subPlayer.sight) 
		{
			if (_subPlayer.rc.right < 0) { _subPlayer.viewX += _subPlayer.speed; }
			else { _subPlayer.x += _subPlayer.speed; }
		}
		else 
		{
			if (_subPlayer.rc.left > WINSIZEX) { _subPlayer.viewX -= _subPlayer.speed; }
			else { _subPlayer.x -= _subPlayer.speed; }
		}
	}
	if (_subPlayer._state == pRUN)
	{
		_subPlayer.speed = 3.0f; 	//pRun일 때는 속도를 3.0f로 설정
		if (_subPlayer.sight)
		{
			if (_subPlayer.rc.left < 0) { _subPlayer.viewX += _subPlayer.speed; }
			else { _subPlayer.x += _subPlayer.speed; }
		}
		else
		{
			if (_subPlayer.rc.right > WINSIZEX) { _subPlayer.viewX -= _subPlayer.speed; }
			else { _subPlayer.x -= _subPlayer.speed; }
		}
	}
	
	//거리조절
	if (_partyDistance > 200)
	{
		_subPlayer._state = pRUN;
		_arrow._chargeTime = 0.0f;
	}
	else if (_partyDistance > 100)
	{
		_subPlayer._state = pWALK;
		_arrow._chargeTime = 0.0f;
	}
	else
	{
		if (_enemyDistance < 100) 
		{ 
			_melee = true; 
			_subPlayer._state = pATTACK;
		}
		else if (_enemyDistance < 500)
		{
			_melee = false;
			_subPlayer._state = pATTACK;
		}
		else
		{
			_subPlayer._state = pIDLE;
			_arrow._chargeTime = 0.0f;
		}
	}

	//공격
	if (_subPlayer._state == pATTACK)
	{
		//근접 상태일 경우 근접 공격을 한다.
		if(_melee)
		{
			_frameIndex = 0;
			if (_subPlayer.sight == true) { _subPlayer.attack = RectMake(_subPlayer.rc.right, _subPlayer.y, 20, 91); }
			else { _subPlayer.attack = RectMake(_subPlayer.rc.left-20, _subPlayer.y, _subPlayer.rc.left, 91); }
		}
		//근접이 아닐시 활을 쏜다.
		else
		{
			//화살 장전 시간이 30.0 이상이고 발사되지 않았을 때
			if (_arrow._chargeTime > 10.0f && !_arrow._bShoot)
			{
				_arrow._bShoot = true;		//화살 발사
				_arrow._chargeTime = 0.0f;	//화살 장전 시간을 초기화.
				_arrow._speed = 2.1f;
				_arrow._point.x = (float(_subPlayer.rc.left) + float((_subPlayer.rc.right - _subPlayer.rc.left) / 2));	//x좌표
				_arrow._point.y = (float(_subPlayer.rc.top) + float((_subPlayer.rc.bottom - _subPlayer.rc.top) / 2));	//y좌표
				_arrow._rc = RectMakeCenter(_arrow._point.x - 1, _arrow._point.y - 1, 17, 11);		//화살 Rect 설정.
				_arrow._flyDirect = _subPlayer.sight;
			}
			else
			{
				//화살충전
				_arrow._chargeTime += 0.1f;
			}
		}
	}


	//화살이 날아갈시 화살의 좌표 이동
	
	if (_arrow._bShoot)
	{
		if (_arrow._flyDirect == true) { _arrow._point.x += cosf(PI / 2) * 2 + _arrow._speed; }
		else { _arrow._point.x -= cosf(PI / 2) * 2 + _arrow._speed; }
		//지금은 y축 안변하니까 주석처리
		//_arrow._point.y += -sinf(PI / 2) * 2;
		//if (_arrow._point.y >= 500) { _arrow._bShoot = false; }
		_arrow._rc = RectMakeCenter(_arrow._point.x - 1, _arrow._point.y - 1, 17, 11); //화살 POINT 이동시켰으니
																					   //화살 RECT도 감
	}

}

void subplayer::render()
{
	Rectangle(getMemDC(), _subPlayer.rc);

	switch (_subPlayer._state)
	{
	case pIDLE:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subIdle")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		else
		{
			IMAGEMANAGER->findImage("subIdle")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		break;
	case pWALK:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subWalk")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		else
		{
			IMAGEMANAGER->findImage("subWalk")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		break;
	case pATTACK:
		if (_melee)
		{
			Rectangle(getMemDC(), _subPlayer.attack);
			if (_subPlayer.sight)
			{
				IMAGEMANAGER->findImage("subMelee")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
			}
			else
			{
				IMAGEMANAGER->findImage("subMelee")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
			}
		}
		else
		{
			if (_subPlayer.sight)
			{
				IMAGEMANAGER->findImage("subShot")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
			}
			else
			{
				IMAGEMANAGER->findImage("subShot")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);

			}
		}
		break;
	case pRUN:
		if (_subPlayer.sight)
		{
			IMAGEMANAGER->findImage("subRun")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		else
		{
			IMAGEMANAGER->findImage("subRun")->frameRender(getMemDC(), _subPlayer.rc.left, _subPlayer.rc.top);
		}
		break;
	default:
		break;
	}
	
	if(_arrow._bShoot)
	{
		IMAGEMANAGER->findImage("arrow")->frameRender(getMemDC(), _arrow._point.x, _arrow._point.y);
	}

	char chr[100];
	sprintf_s(chr, "거리 : %f", _enemyDistance);
	TextOut(getMemDC(), 100, 150, chr, strlen(chr));

	char chr1[100];
	sprintf_s(chr1, "화살충전시간 : %f", _arrow._chargeTime);
	TextOut(getMemDC(), 100, 200, chr1, strlen(chr1));
}

void subplayer::animation()
{
	switch (_subPlayer._state)
	{
	case pIDLE:				  //대기상태
	{
		if (_subPlayer.sight)
		{
			_frameCount++;
			_subPlayer.idle->setFrameY(0);
			if (_frameCount % 16 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 2)
				{
					_frameIndex = 0;
				}
				_subPlayer.idle->setFrameX(_frameIndex);
			}
		}
		else
		{
			_frameCount++;
			_subPlayer.idle->setFrameY(1);
			if (_frameCount % 16 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 1;
				}
				_subPlayer.idle->setFrameX(_frameIndex);
			}
		}
		break;
	}
	case pWALK:		//걷기
	{
		if (_subPlayer.sight)
		{
			_frameCount++;
			_subPlayer.walk->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 4)
				{
					_frameIndex = 0;
				}
				_subPlayer.walk->setFrameX(_frameIndex);
			}
		}
		else
		{
			_frameCount++;
			_subPlayer.walk->setFrameY(1);
			if (_frameCount % 8 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 3;
				}
				_subPlayer.walk->setFrameX(_frameIndex);
			}
		}
		break;
	}
	case pATTACK:
		if (_melee)	//근접 공격을 할 때
		{
			_frameCount++;
			if (_subPlayer.sight)
			{
				_subPlayer.atkmelee->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
						//근접 공격의 이미지 프레임은 2개
						//따라서 _frameIndex가 1보다 큰 경우는 공격이 끝난 것으로 판단한다.
					{
						_frameCount = 0;	//_frameCount를 0으로 초기화
						_frameIndex = 0;	//_frameIndex를 0으로 초기화
						_subPlayer._state = pIDLE;		//대기상태로 전환
					}
					_subPlayer.atkmelee->setFrameX(_frameIndex);
				}
			}
			else
			{
				_subPlayer.atkmelee->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0)
						//근접 공격의 이미지 프레임은 2개
						//따라서 _frameIndex가 1보다 큰 경우는 공격이 끝난 것으로 판단한다.
					{
						_frameCount = 0;	//_frameCount를 0으로 초기화
						_frameIndex = 1;	//_frameIndex를 0으로 초기화
						_subPlayer._state = pIDLE;		//대기상태로 전환
					}
					_subPlayer.atkmelee->setFrameX(_frameIndex);
				}
			}
		}
		else	//원거리 공격을 할 때
		{
			if (_subPlayer.sight)
			{
				_frameCount++;
				_subPlayer.atkshot->setFrameY(0);
				if (_frameCount % 8 == 0)
				{
					_frameIndex++;
					if (_arrow._bShoot == false) { _frameIndex = 2; }	//발사를 아직 안했다면 프레임 반복
					if (_frameIndex > 7)
						//원거리 공격의 이미지 프레임은 8개
						//따라서 _frameIndex가 7보다 큰 경우는 공격이 끝난 것으로 판단한다.
					{
						_frameCount = 0;	//_frameCount를 0으로 초기화
						_frameIndex = 0;						//_frameIndex를 0으로 초기화
						_subPlayer._state = pIDLE;		//대기상태로 전환
					}
					_subPlayer.atkshot->setFrameX(_frameIndex);
				}
			}
			else
			{
				_frameCount++;
				_subPlayer.atkshot->setFrameY(1);
				if (_frameCount % 8 == 0)
				{
					_frameIndex--;
					if (_arrow._bShoot == false) { _frameIndex = 4; }	//발사를 아직 안했다면 프레임 반복
					if (_frameIndex < 1)
						//원거리 공격의 이미지 프레임은 8개
						//따라서 _frameIndex가 7보다 큰 경우는 공격이 끝난 것으로 판단한다.
					{
						_frameCount = 0;	//_frameCount를 0으로 초기화
						_frameIndex = 0;	//_frameIndex를 0으로 초기화
						_subPlayer._state = pIDLE;		//대기상태로 전환
					}
					_subPlayer.atkshot->setFrameX(_frameIndex);
				}
			}
		}
		break;

	case pRUN:
	{
		if(_subPlayer.sight)
		{
			_frameCount++;
			_subPlayer.run->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 4)
				{
					_frameIndex = 0;
				}
				_subPlayer.run->setFrameX(_frameIndex);
			}
		}
		else
		{
			_frameCount++;
			_subPlayer.run->setFrameY(1);
			if (_frameCount % 8 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 3;
				}
				_subPlayer.run->setFrameX(_frameIndex);
			}
		}
		break;
	}
	default:
		break;
	}

	if (_subPlayer.sight) { _arrow._img->setFrameY(0); }
	else { _arrow._img->setFrameY(1); }
}

void subplayer::walkingInfo()
//상태창에서 걷은 애니메이션 출력
{
	_frameCount++;

	switch(_direct%4)
	{
	case 0:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 3;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	case 1:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 2;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	case 2:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 0;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	case 3:
	{
		_walkingDirect->setFrameY(_direct);
		if (_frameCount % 10 == 0)
		{
			if (_isLeft) { _frameIndex++; }
			else { _frameIndex--; }
			if (_frameIndex == 4 || _frameIndex == 0) { _isLeft = !_isLeft; }
		}
		if (_frameCount % 90 == 0)
		{
			_direct = 1;
		}
		_walkingDirect->setFrameX(_frameIndex);
		break;
	}
	default:
		break;
	}
}

void subplayer::checkDistanceWithPlayer(float x)
{
	_partyDistance = sqrt(powf(x - _subPlayer.viewX, 2.0f));
	if (x < _subPlayer.viewX) { _subPlayer.sight = 0; }
	else { _subPlayer.sight = 1; }
}

void subplayer::checkDistanceWithEnemy(float x)
{
	_enemyDistance = sqrt(powf(x - _subPlayer.viewX, 2.0f));
	if (_subPlayer._state == pATTACK)
	{
		if (x < _subPlayer.viewX) { _subPlayer.sight = 0; }
		else { _subPlayer.sight = 1; }
	}
}

void subplayer::checkArrowHitTheEnemy(bool b)
{
	if (_arrow._bShoot == true)
	{
		_arrow._bShoot = !b;	//충돌했으면 화살 발사 false 처리
								//아니면 계속 날아감
	}

}
