#pragma once
#include "gameNode.h"

enum tagstate
{
	pIDLE,
	pDEAD,
	pRUN,
	pWALK,
	pJUMP,
	pATTACK,
	pGUARD,
	pWIN
};

struct tagPlayer
{
	bool sight;	 //플레이어 시각(0 - 왼쪽, 1 - 오른쪽)
	int lv;				//플레이어 LV
	int maxHp, hp;		 //플레이어 hp
	int maxTp, tp;		// 플레이어 tp
	int attXK, attYK;
	float x, y;    //플레이어 좌표
	float inGameX, inGameY;	//전투가 아니라 인게임 내에서 쓸 좌표
	float speed;
	float gravity;  //중력값

	image* idle;
	image * walk;
	image* run;
	image* guard;

	image* atkSlash;
	image* atkstab;
	image* atkshot;
	image* atkmelee;
	image* jump;

	image * dead;
	image* win;

	RECT rc;  //플레이어 충돌 사각형

	RECT attack;      //공격 충돌 사각형
	//RECT jumpAttack;  //공격 충돌 사각형
	//float atkTime;
};
class player : public gameNode
{
private:
	//프레임 이미지 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;

private:
	RECT _stage;		//지형
	RECT _playerDoorRc;	// 플레이어가 문에 닿았는지 확인해주는 렉트
	float _enemyCenterX, _enemyCenterY;		//사각형 중앙

	//float _immoTime;		//충돌시 무적시간

	//태그 상태
	tagstate _state;

	int _direct;		// 플레이어가 왼쪽을 보고 있는지
						//0: 위, 1: 아래, 2: 좌, 3: 우

	bool _isBattle;	//플레이어가 현재 배틀씬인지 아닌지

public:

	HRESULT init();
	void release();
	void update();
	void render();



	//float getenemyCenterx() { return _enemyCenterX; }
	//float getenemyCentery() { return _enemyCenterY; }
	//RECT getenemyRect() { return _TESTenemy; }

	//enum태그 변화에 따라 변하는 플레이어 모션
	void animation();
	tagPlayer* getPlayer() { return &_player; }
	void setPlayer(tagPlayer player) { _player = player; }

	//플레이어의 X,Y좌표를 주기위한 get함수
	float getPlayerX() { return _player.inGameX; }
	float getPlayerY() { return _player.inGameY; }
	//맵이 이동했을 때 플레이어의 위치를 조정해줘야 하므로 set으로 플레이어의 x,y값과 렉트값을 바꿔준다.
	void setPlayerRect(int x, int y);
	//상태창을 열었을 때 이미지가 계속 움직이려면 pWALK상태여야 하므로 상태를 바꿔줘야 한다.
	void setPlayerState(tagstate state) { _state = state; }
	//상태창에 들어갔을 떄와 나왔을 떄 같은 곳을 바라보고 있어야 하니 방향을 가르쳐줘야한다.
	int getDirect() { return _direct; }
	//그리고 받을 수도 있어야 한다.
	void setDirect(int direct) { _direct = direct; }
	//플레이어의 렉트를 주기위한 get함수
	RECT getPlayerRc() { return _player.rc; }
	//플레이어가 문 근처에 있는지 확인하기 위한 get함수
	RECT getPlayerDoorRc() { return _playerDoorRc; }

	// 플레이어 구조체를 초기화 하는 함수
	void settingTagPlayer();
	// 플레이어 도어렉트 플레이어 위치에 따라 위치를 조정해주는 함수.
	void settingPlayerDoorRect();
	// 스테이트 창 틀었을 때 캐릭터가 회전하는 이미지
	void spinPlayer();


	player() {}
	~player() {}
};

class subplayer : public gameNode
{
private:
	//프레임 이미지 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;

	player* _mainplayer;

	//private:
	//	bool _sight;	 //플레이어 시각(0 - 왼쪽, 1 - 오른쪽)
	//	int _hp;		 //플레이어 hp
	//	float _x, _y;    //플레이어 좌표
	//	float _speed;
	//	float _gravity;  //중력값
	//
	//private:
	//	image* _idle;
	//	image * _walk;
	//	image* _run;
	//	image* _guard;
	//
	//	image* _atkSlash;
	//	image* _atkstab;
	//	image* _jump;
	//	
	//	image * _dead;
	//	image* _win;

private:
	RECT _rcPlayer;		//플레이어 충돌 사각형
	float _chargeTime;	//화살 장전 시간

	float _distance;	//ai와 적의 거리
	float _cX, _cY;		//ai사각형 중앙
	float _speed;		//화살속도

	RECT _arrow;		//화살 사각형
	image* _arrowImg;		//화살 사각형
	bool _arrowIs;		//화살 날라가는여부
	bool _melee;		//근접공격여부

	//태그 상태
	tagstate _state;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	//enum태그 변화에 따라 변하는 플레이어 모션
	void animation();


	subplayer() {}
	~subplayer() {}
};

