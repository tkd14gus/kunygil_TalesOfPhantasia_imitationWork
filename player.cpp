#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	//이미지 초기화
	_player.idle = IMAGEMANAGER->addFrameImage("mIdle", "Images/mainplayer/idle.bmp", 250, 260, 2, 2);
	_player.walk = IMAGEMANAGER->addFrameImage("walk", "Images/mainplayer/walk.bmp", 450, 260, 4, 2);
	_player.run = IMAGEMANAGER->addFrameImage("run", "Images/mainplayer/run&stop.bmp", 628, 314, 5, 2);
	_player.guard = IMAGEMANAGER->addFrameImage("guard", "Images/mainplayer/guard.bmp", 110, 260, 1, 2);

	//공격모션
	_player.atkSlash = IMAGEMANAGER->addFrameImage("slash", "Images/mainplayer/atk_slash.bmp", 874, 437, 5, 2);
	//_player.atkstab = IMAGEMANAGER->addFrameImage("stab", "Images/mainplayer/atk_stab.bmp", 396, 120, 4, 2);
	_player.jump = IMAGEMANAGER->addFrameImage("jump", "Images/mainplayer/jump_slash.bmp", 749, 347, 5, 2);

	_player.dead = IMAGEMANAGER->addFrameImage("dead", "Images/mainplayer/dead.bmp", 440, 260, 4, 2);

	_player.win = IMAGEMANAGER->addFrameImage("win", "Images/mainplayer/victory.bmp", 669, 262, 4, 1);


	_stage = RectMake(0, 500, WINSIZEX, WINSIZEY);


	//플레이어 초기 좌표 설정
	_player.x = 400;
	_player.y = 370;
	//플레이어 사각형


	_enemyX = 700;
	_enemyY = 200;


	_player.sight = true;		//초기 설정 - 오른쪽 방향
	_player.atkTime = 0.0f;     //타격시간
	_state = IDLE;		        //초기 설정 - 대기상태

	if (_state == WALK)
	{
		_player.speed = 1.0f;
	}
	else if (_state == RUN)
	{
		_player.speed = 3.0f;
	}

	_player.hp = 5;			//초기 설정 - 체력 5

	//프레임이미지초기화
	_frameCount = 0;
	_frameIndex = 0;

	//무적시간 초기화
	_immoTime = 0;

	_enemyHP = 3;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	//실시간 플레이어 위치
	_rcPlayer = RectMake(_player.x, _player.y, 125, 130);

	//실시간 적의 위치
	_TESTenemy = RectMake(_enemyX, _enemyY, 500, 500);

	//적사각형 중점
	_enemyCenterX = _enemyX + float((_TESTenemy.right - _TESTenemy.left) / 2);
	_enemyCenterY = _enemyY + float((_TESTenemy.bottom - _TESTenemy.top) / 2);

	//test - HP down
	if (INPUT->GetKeyDown('Q'))
	{
		_player.hp--;
	}

	//sight left & walk left
	if (INPUT->GetKey(VK_LEFT))
	{
		if (_state == ATTACK)
		{
			_state = ATTACK;
		}
		else if (_state == GUARD)
		{
			_state = GUARD;
		}
		else if (_state == JUMP)
		{
			_state = JUMP;
			_player.x -= 2;
		}
		else
		{
			if (INPUT->GetKey(VK_SHIFT))
			{
				_player.sight = 0;				 //플레이어 시점 - 왼쪽
				_state = RUN;			 //플레이어 상태 - 뛰기
				_player.x -= 3;                    //플레이어 좌표 변화
			}
			else
			{
				_player.sight = 0;				 //플레이어 시점 - 왼쪽
				_state = WALK;			 //플레이어 상태 - 걷기
				_player.x -= 1;                    //플레이어 좌표 변화
			}
		}
	}
	//state idle
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		_player.sight = 0;
		_state = IDLE;
	}
	//sight right & walk right
	if (INPUT->GetKey(VK_RIGHT))
	{
		if (_state == ATTACK)
		{
			_state = ATTACK;
		}
		else if (_state == GUARD)
		{
			_state = GUARD;
		}
		else if (_state == JUMP)
		{
			_state = JUMP;
			_player.x += 2;
		}
		else
		{
			if (INPUT->GetKey(VK_SHIFT))
			{
				_player.sight = 1;				 //플레이어 시점 - 오른쪽
				_state = RUN;			         //플레이어 상태 - 뛰기
				_player.x += 3;                  //플레이어 좌표 변화
			}
			else
			{
				_player.sight = 1;				 //플레이어 시점 - 오른쪽
				_state = WALK;			         //플레이어 상태 - 걷기
				_player.x += 1;                  //플레이어 좌표 변화
			}
		}
	}
	//state idle
	if (INPUT->GetKeyUp(VK_RIGHT))
	{
		_player.sight = 1;
		_state = IDLE;
	}


	//test - state attack -> 베기와 찌르기, 점프시에는 점프 베기 찌르기등으로 추가예정
	if (INPUT->GetKeyDown('Z'))
	{
		_state = ATTACK;
		_frameIndex = 0;
	}

	//test - state guard
	if (INPUT->GetKey('X'))
	{
		_state = GUARD;
	}
	if (INPUT->GetKeyUp('X'))
	{
		_state = IDLE;
	}

	// state jump
	if (INPUT->GetKeyDown('C') && _state != JUMP)
	{
		_frameIndex = 0;
		_state = JUMP;
		_player.gravity = 0.0f;
	}

	if (_state == JUMP)
	{
		_player.x += cosf(PI / 2) * 1;
		_player.y += -sinf(PI / 2) * 5 + _player.gravity;
		_player.gravity += 0.1f;
	}



	//test - state win
	if (INPUT->GetKeyDown(VK_F5))
	{
		_state = WIN;
	}

	//바닥에 닿게 되었을때
	if (_player.y > 370 && _state == JUMP)
	{
		_player.gravity = 0.0f;
		_state = IDLE;
		_player.y = 370;
	}
	//공중에서 다른 모션이 적용되지 않도록 설정
	if (_player.y < 370 && _state != JUMP)
	{
		_state = JUMP;
	}

	//플레이어 사망
	if (_player.hp < 0)
	{
		_state = DEAD;
	}
}

void player::render()
{

	Rectangle(getMemDC(), _rcPlayer);		//플레이어 타격범위 사각형

	Rectangle(getMemDC(), _stage);

	if (_enemyHP > 0)
	{
		Rectangle(getMemDC(), _TESTenemy);
	}

	if (_state == ATTACK)
	{
		_player.atkTime += 0.1f;
		if (_player.sight == true)
		{
			_player.attack = RectMake(_rcPlayer.right + 20, _rcPlayer.top, 10, 130);
			Rectangle(getMemDC(), _player.attack);
		}
		else if (_player.sight == false)
		{
			_player.attack = RectMake(_rcPlayer.left - 20, _rcPlayer.top, 10, 130);
			Rectangle(getMemDC(), _player.attack);
		}
	}

	if (_state == JUMP)
	{
		_player.atkTime += 0.1f;
		if (_player.sight == true)
		{
			_player.jumpAttack = RectMake(_rcPlayer.right - 20, _rcPlayer.top, 50, 160);
			Rectangle(getMemDC(), _player.jumpAttack);
		}
		else if (_player.sight == false)
		{
			_player.jumpAttack = RectMake(_rcPlayer.left - 20, _rcPlayer.top, 50, 160);
			Rectangle(getMemDC(), _player.jumpAttack);
		}
	}

	RECT temp;
	//공격 타격범위와 적과의 충돌
	if (IntersectRect(&temp, &_player.attack, &_TESTenemy)&& _immoTime < 0.1f)
	{
		_immoTime += 0.1f;
		_player.attack.bottom = 0;
		_player.attack.top = 0;
		_player.attack.left = 0;
		_player.attack.right = 0;
		_enemyHP -= 1;
	}

	if (_immoTime >= 0.1f)
	{
		_immoTime += 0.1f;
		if (_immoTime > 10.0f)
		{
			_immoTime = 0.0f;
		}
	}
	

	this->animation();					//플레이어 모션 애니메이션

	char chr[100];
	sprintf(chr, "ENEMY HP : %d", _enemyHP);
	TextOut(getMemDC(), 100, 100, chr, strlen(chr));

	char chr1[100];
	sprintf(chr1, "immotal Timer : %f", _immoTime);
	TextOut(getMemDC(), 100, 120, chr1, strlen(chr1));



}

void player::animation()
{
	switch (_state)
	{
	case IDLE:		//대기상태
		//좌
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("mIdle", getMemDC(), _rcPlayer.left, _rcPlayer.top);
			_frameCount++;
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
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("mIdle", getMemDC(), _rcPlayer.left, _rcPlayer.top);
			_frameCount++;
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
	case WALK:		//걷기
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("walk", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top);
			_frameCount++;
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
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("walk", getMemDC(), _rcPlayer.left + 10, _rcPlayer.top);
			_frameCount++;
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
	case RUN:		//달리기
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("run", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 10);
			_frameCount++;
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
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("run", getMemDC(), _rcPlayer.left, _rcPlayer.top - 10);
			_frameCount++;
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
	case ATTACK:	//공격은 한번공격후 다시 대기상태로 들어가게 했음
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("slash", getMemDC(), _rcPlayer.left - 15, _rcPlayer.top - 20);
			_frameCount++;
			_player.atkSlash->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				IMAGEMANAGER->findImage("slash")->setFrameY(0);
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameCount = 0;
					_frameIndex = 0;
					_state = IDLE;	//한번공격후 상태대기자세로
				}
				_player.atkSlash->setFrameX(_frameIndex);
			}
		}
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("slash", getMemDC(), _rcPlayer.left - 15, _rcPlayer.top - 20);
			_frameCount++;
			_player.atkSlash->setFrameY(1);
			if (_frameCount % 8 == 0)
			{
				IMAGEMANAGER->findImage("slash")->setFrameY(1);
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
					_state = IDLE;
				}
				_player.atkSlash->setFrameX(_frameIndex);
			}
		}
		break;
	case JUMP:
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("jump", getMemDC(), _rcPlayer.left, _rcPlayer.top - 20);
			_frameCount++;
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
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("jump", getMemDC(), _rcPlayer.left, _rcPlayer.top - 20);
			_frameCount++;
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
	case GUARD:		//가드
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("guard", getMemDC(), _rcPlayer.left, _rcPlayer.top);
			_frameCount++;
			_player.atkSlash->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				IMAGEMANAGER->findImage("guard")->setFrameY(0);
				_frameIndex++;
				if (_frameIndex > 1)
				{
					_frameCount = 0;
					_frameIndex = 0;
				}
				_player.atkSlash->setFrameX(_frameIndex);
			}
		}
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("guard", getMemDC(), _rcPlayer.left, _rcPlayer.top);
			_frameCount++;
			_player.atkSlash->setFrameY(1);
			if (_frameCount % 8 == 0)
			{
				IMAGEMANAGER->findImage("guard")->setFrameY(1);
				_frameIndex++;
				if (_frameIndex > 1)
				{
				}
				_player.atkSlash->setFrameX(_frameIndex);
			}
		}
		break;
	case DEAD:		//사망시에는 hp = 0이되어 사망하며 유령상태 유지 - 이후 재시작등 수정 가능
		if (_player.sight == false)
		{
			IMAGEMANAGER->frameRender("dead", getMemDC(), _rcPlayer.left, _rcPlayer.top);
			_frameCount++;
			_player.dead->setFrameY(0);
			if (_frameCount % 30 == 0)
			{
				IMAGEMANAGER->findImage("dead")->setFrameY(0);
				_frameIndex++;
				_player.dead->setFrameX(_frameIndex);
			}
		}
		if (_player.sight == true)
		{
			IMAGEMANAGER->frameRender("dead", getMemDC(), _rcPlayer.left, _rcPlayer.top);
			_frameCount++;
			_player.dead->setFrameY(1);
			if (_frameCount % 30 == 0)
			{
				IMAGEMANAGER->findImage("dead")->setFrameY(1);
				_frameIndex++;
				_player.dead->setFrameX(_frameIndex);
			}
		}
		break;
	case WIN:
		IMAGEMANAGER->frameRender("win", getMemDC(), _rcPlayer.left - 30, _rcPlayer.top - 90);
		_frameCount++;
		_player.win->setFrameY(0);
		if (_frameCount % 20 == 0)
		{
			IMAGEMANAGER->findImage("win")->setFrameY(0);
			_frameIndex++;
			_player.win->setFrameX(_frameIndex);
		}
		break;
	}
}

HRESULT subplayer::init()
{

	_mainplayer = new player;
	_mainplayer->init();


	//이미지 초기화
	_player.idle = IMAGEMANAGER->addFrameImage("subIdle", "Images/subplayer/chester_battel_idle.bmp", 288, 180, 2, 1);
	_player.walk = IMAGEMANAGER->addFrameImage("subWalk", "Images/subplayer/chester_battel_walk.bmp", 576, 180, 4, 1);
	//_player.run = IMAGEMANAGER->addFrameImage("run", "Images/subplayer/chester_battel_run.bmp", 576, 180, 4, 1);
	//_player.guard = IMAGEMANAGER->addFrameImage("guard", "Images/mainplayer/guard.bmp", 110, 260, 1, 1);

	//공격모션
	_player.atkshot = IMAGEMANAGER->addFrameImage("subShot", "Images/subplayer/chester_battel_shoot.bmp", 1152, 180, 8, 1);
	_player.atkmelee = IMAGEMANAGER->addFrameImage("subMelee", "Images/subplayer/chester_battel_physical.bmp", 288, 180, 2, 1);
	//_player.atkstab = IMAGEMANAGER->addFrameImage("stab", "Images/subplayer/mainplayer/atk_stab.bmp", 396, 120, 4, 2);
	//_player.jump = IMAGEMANAGER->addFrameImage("jump", "Images/mainplayer/jump_slash.bmp", 749, 347, 5, 1);

	_player.dead = IMAGEMANAGER->addFrameImage("subDead", "Images/subplayer/chester_battel_dead.bmp", 432, 180, 3, 1);

	_player.win = IMAGEMANAGER->addFrameImage("subWin", "Images/subplayer/chester_battel_win.bmp", 432, 180, 3, 1);


	_arrowImg = IMAGEMANAGER->addImage("arrow", "Images/subplayer/arrow.bmp", 76, 11);



	//플레이어 초기 좌표 설정
	_player.x = 100;
	_player.y = 370;
	//플레이어 사각형



	_player.sight = true;		//초기 설정 - 오른쪽 방향

	_state = IDLE;		        //초기 설정 - 대기상태

	_chargeTime = 0.0f;			//화살준비 시간(일정시간을 채울시 발사할 예정)
	_arrowIs = false;			//화살안날아간 상태 true가 될시 화살은 날아가는중
	_speed = 0.0f;

	_melee = false;					//거리가 일정 거리가 될경우 true값이 되어 공격시 근접공격으로 전환

	//if (_state == WALK)
	//{
	//	_player.speed = 1.0f;
	//}
	//else if (_state == RUN)
	//{
	//	_player.speed = 3.0f;
	//}

	_player.hp = 5;			//초기 설정 - 체력 5

	//프레임이미지초기화
	_frameCount = 0;
	_frameIndex = 0;

	return S_OK;
}

void subplayer::release()
{
	_mainplayer->release();
	SAFE_DELETE(_mainplayer);
}

void subplayer::update()
{

	//ai의 위치
	_rcPlayer = RectMake(_player.x, _player.y, 125, 130);

	//중점의 위치
	_cX = (float(_rcPlayer.left) + float((_rcPlayer.right - _rcPlayer.left) / 2));
	_cY = (float(_rcPlayer.top) + float((_rcPlayer.bottom - _rcPlayer.top) / 2));

	//메인플레이어의 위치를 받기위한
	_mainplayer->update();


	//실시간 거리
	//ai와 적의 거리
	_distance = sqrt(pow(_cX - _mainplayer->getenemyCenterx(), 2) + pow(_cY - _mainplayer->getenemyCentery(), 2));


	//화살충전
	_chargeTime += 0.1f;

	//충전완료
	if (_chargeTime > 30.0f&& _arrowIs == false)
	{
		_chargeTime = 0.0f;
		_state = ATTACK;
	}
	else if (_frameIndex == 0)
	{
		_state = IDLE;
	}

	//거리조절
	if (_distance > 700)
	{
		_state = WALK;
		_player.x++;
	}
	else if(_distance)
	{
		
	}

	//공격
	if (_state == ATTACK)
	{
		//근접이 아닐시 활을 쏜다.
		if (_melee == false)
		{
			//화살이 날아갑니다.
			_arrowIs = true;
		}
		if (_melee == true)
		{

		}
	}


	//화살이 날아갈시 화살의 좌표 이동
	if (_arrowIs == true)
	{
		_cX += cosf(PI / 2) * 2 + _speed;
		_cY += -sinf(PI / 2) * 2;
		_speed += 2.1f;
	}

	if (INPUT->GetKey('W'))
	{
		_cX += cosf(PI / 2) * 2 + _speed;
	}
	if (INPUT->GetKey('S'))
	{
		_cX -= cosf(PI / 2) * 2 + _speed;
	}

	//화살충돌
	RECT temp;
	if (IntersectRect(&temp, &_mainplayer->getenemyRect(), &_arrow))
	{
		_arrowIs = false;
	}

	//ai 움직임 확인용
	if (INPUT->GetKey('A'))
	{
		_player.x--;
	}
	if (INPUT->GetKey('D'))
	{
		_player.x++;
	}

}

void subplayer::render()
{
	Rectangle(getMemDC(), _rcPlayer);






	this->animation();
	_arrow = RectMakeCenter(_cX - 1, _cY - 1, 17, 11);

	if (_arrowIs == true)
	{
		Rectangle(getMemDC(), _arrow);
		LineMake(getMemDC(), _cX, _cY, _mainplayer->getenemyCenterx(), _mainplayer->getenemyCentery());
		IMAGEMANAGER->rotateRender("arrow", getMemDC(), _cX, _cY, (_cX, _cY));
	}

	char chr[100];
	sprintf(chr, "거리 : %f", _distance);
	TextOut(getMemDC(), 100, 150, chr, strlen(chr));

	char chr1[100];
	sprintf(chr1, "화살충전시간 : %f", _chargeTime);
	TextOut(getMemDC(), 100, 200, chr1, strlen(chr1));
}

void subplayer::animation()
{
	switch (_state)
	{
	case IDLE:		//대기상태
		IMAGEMANAGER->frameRender("subIdle", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 30);
		_frameCount++;
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
		break;
	case WALK:		//걷기
		IMAGEMANAGER->frameRender("subWalk", getMemDC(), _rcPlayer.left - 20, _rcPlayer.top - 30);
		_frameCount++;
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
		break;

	case ATTACK:
		if (_melee == false)
		{
			IMAGEMANAGER->frameRender("subShot", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 30);
			_frameCount++;
			_player.atkshot->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 8)
				{
					_frameCount = 0;
					_frameIndex = 0;
					_state = IDLE;
				}
				_player.atkshot->setFrameX(_frameIndex);
			}
		}
		else if (_melee = true)
		{
			IMAGEMANAGER->frameRender("subMelee", getMemDC(), _rcPlayer.left - 10, _rcPlayer.top - 30);
			_frameCount++;
			_player.atkmelee->setFrameY(0);
			if (_frameCount % 8 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 2)
				{
					_frameCount = 0;
					_frameIndex = 0;
					_state = IDLE;
				}
				_player.atkmelee->setFrameX(_frameIndex);
			}
		}

		break;
	}
}
