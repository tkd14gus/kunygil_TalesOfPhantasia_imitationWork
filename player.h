#pragma once
#include "gameNode.h"

enum tagstate
{
	IDLE,
	DEAD,
	RUN,
	WALK,
	JUMP,
	ATTACK,
	GUARD,
	WIN
};

struct tagPlayer
{
	bool sight;	 //플레이어 시각(0 - 왼쪽, 1 - 오른쪽)
	int hp;		 //플레이어 hp
	float x, y;    //플레이어 좌표
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

	RECT player;  //플레이어 충돌 사각형

	RECT attack;      //공격 충돌 사각형
	RECT jumpAttack;  //공격 충돌 사각형
	float atkTime;
};
class player : public gameNode
{
private:
	//프레임 이미지 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;


	//적군충돌 테스트
	RECT _TESTenemy;
	float _enemyX, _enemyY;
	int _enemyHP;

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
	RECT _stage;		//지형
	float _enemyCenterX, _enemyCenterY;		//사각형 중앙

	float _immoTime;		//충돌시 무적시간

	//태그 상태
	tagstate _state;

public:

	HRESULT init();
	void release();
	void update();
	void render();



	float getenemyCenterx() { return _enemyCenterX; }
	float getenemyCentery() { return _enemyCenterY; }
	RECT getenemyRect() { return _TESTenemy; }

	//enum태그 변화에 따라 변하는 플레이어 모션
	void animation();


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

